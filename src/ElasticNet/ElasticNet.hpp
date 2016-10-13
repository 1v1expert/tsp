#pragma once

#include <memory>
#include <algorithm>
#include <numeric>
#include <fstream>

#include "Parameters.hpp"
#include "MathUtility.hpp"
#include "NeuronUtility.hpp"
#include "Solution.hpp"

namespace tsp
{
	using std::unique_ptr;

	using std::max;
	using std::max_element;
	using std::min_element;
	using std::minmax_element;
	using std::accumulate;
	using std::for_each;
	using std::generate;
	using std::transform;
	using std::accumulate;
	using std::make_unique;

	template<typename DistanceType>
	class NodeContainer;

	template<typename DistanceType>
	class ElasticNet
	{
	public:
		explicit ElasticNet(unique_ptr<NodeContainer<DistanceType>>);
		ElasticNet(const ElasticNet&) = delete;
		ElasticNet(ElasticNet&&) = default;
		ElasticNet& operator=(const ElasticNet&) = delete;
		ElasticNet& operator=(ElasticNet&&) = default;

		unique_ptr<NodeContainer<DistanceType>> Run(ostream& log_stream = std::cout);

	private:
		unique_ptr<NodeContainer<DistanceType>> original_nodes_;
		unique_ptr<NodeContainer<DistanceType>> nodes_;
		uint64_t iteration_count_;
		double k_;
		uint32_t neurons_count_;

		vector<Neuron> neurons_;
		vector<vector<vector<double>>> delta_;
		vector<vector<double>> dist2_;
		double worst_dist_;
		vector<vector<double>> weights_;

		void NormalizeNodes();
		void InitNeurons();
		void UpdateK();
		void UpdateWeights();
		void UpdateNeurons();
		bool StopCriteria() const;
		bool Iteration();

		vector<vector<double>> DistForce();
		vector<vector<double>> LenghtForce();
	};

	template <typename DistanceType>
	ElasticNet<DistanceType>::ElasticNet(unique_ptr<NodeContainer<DistanceType>> nodes) :
		original_nodes_(move(nodes)),
		nodes_(make_unique<NodeContainer<DistanceType>>(*original_nodes_)),
		iteration_count_(0ul),
		k_(ElasticNetParameters["init_k"]),
		neurons_count_(ElasticNetParameters["num_neurons_factor"] * nodes_->NodesCount())
	{
		NormalizeNodes();
		InitNeurons();
	}

	template <typename DistanceType>
	unique_ptr<NodeContainer<DistanceType>>
		ElasticNet<DistanceType>::Run(ostream& log_stream)
	{
		while (Iteration())
		{
			if (iteration_count_ % 100 == 0)
				log_stream << "Iteration #" << iteration_count_ << " Worst d: " << worst_dist_ << '\n';
		}
		return Solution<DistanceType>::DecodeSolution(dist2_, *original_nodes_);
	}

	template <typename DistanceType>
	bool ElasticNet<DistanceType>::Iteration()
	{
		iteration_count_++;

		UpdateK();
		UpdateWeights();
		UpdateNeurons();

		return !StopCriteria();
	}

	template <typename DistanceType>
	void ElasticNet<DistanceType>::NormalizeNodes()
	{
		auto minmax_x = minmax_element(nodes_->cbegin(),
									   nodes_->cend(),
									   [](const auto& t1, const auto& t2) { return t1->X() < t2->X(); });
		auto minmax_y = minmax_element(nodes_->cbegin(),
									   nodes_->cend(),
									   [](const auto& t1, const auto& t2) { return t1->Y() < t2->Y(); });
		auto min_x = (*minmax_x.first)->X();
		auto max_x = (*minmax_x.second)->X();
		auto min_y = (*minmax_y.first)->Y();
		auto max_y = (*minmax_y.second)->Y();

		for_each(nodes_->begin(), 
			     nodes_->end(), 
				 [&](auto& n)
		{
			n->SetX((n->X() - min_x) / (max_x - min_x));
			n->SetY((n->Y() - min_y) / (max_y - min_y));
		});
	}

	template <typename DistanceType>
	void ElasticNet<DistanceType>::InitNeurons()
	{
		// Initialize the neurons in a circle at the center of the
		// cities.

		auto theta = vector<double>(neurons_count_);
		auto last = 0.;
		for_each(theta.begin(), theta.end(), [&](auto& t) { t = last; last += 2 * pi / neurons_count_; });
		auto centroid_x = accumulate(nodes_->begin(), 
								     nodes_->end(), 
								     0.0,
								     [](auto& t1, auto& t2) { return t1 + t2->X(); }) / nodes_->NodesCount();
		auto centroid_y = accumulate(nodes_->begin(),
									 nodes_->end(),
									 0.0,
									 [](auto& t1, auto& t2) { return t1 + t2->Y(); }) / nodes_->NodesCount();

		for_each(theta.cbegin(), 
			     theta.cend(), 
			     [&](const auto& t) { neurons_.push_back({cos(t), sin(t)}); });
		for_each(neurons_.begin(),
			     neurons_.end(),
			     [](auto& n) { n.X *= ElasticNetParameters["radius"]; 
			     	           n.Y *= ElasticNetParameters["radius"]; });
		for_each(neurons_.begin(),
				 neurons_.end(),
				 [&](auto& n) { n.X += centroid_x; n.Y += centroid_y; });
	}

	template <typename DistanceType>
	void ElasticNet<DistanceType>::UpdateK()
	{
		if (iteration_count_ %
			static_cast<uint64_t>(ElasticNetParameters["k_update_period"]) == 0)
			k_ = max(0.001, ElasticNetParameters["k_alpha"] * k_);
	}

	template <typename DistanceType>
	void ElasticNet<DistanceType>::UpdateWeights()
	{
		// Finding delta
		delta_.clear();
		for (const auto& node: *nodes_)
		{
			vector<vector<double>> neurons;
			for_each(neurons_.begin(), neurons_.end(), [&](auto& n) {neurons.push_back({ node->X() - n.X,
																						 node->Y() - n.Y }); });
			delta_.emplace_back(neurons);
		}

		// Finding dist2
		dist2_.clear();
		for (const auto& t1: delta_)
		{
			dist2_.emplace_back(vector<double>());
			for_each(t1.cbegin(), 
					 t1.cend(), 
					 [&](const auto& t2) {dist2_.back().emplace_back(t2[0] * t2[0] + t2[1] * t2[1]); });
		}

		// Finding worst_dist
		vector<double> mins(dist2_.size());
		transform(dist2_.cbegin(), 
				  dist2_.cend(),
				  mins.begin(), 
				  [](const auto& d) { return *min_element(d.begin(), d.end()); });
		worst_dist_ = sqrt(*max_element(mins.begin(), mins.end()));

		// Finding unnormalized weights
		weights_.clear();
		for (const auto& d : dist2_)
		{
			weights_.emplace_back(vector<double>());
			for_each(d.cbegin(),
					 d.cend(),
					 [&](const auto& w) { weights_.back().emplace_back(exp(-w / (2 * (k_ * k_)))); });
		}

		// Normalize weights
		for (auto& w : weights_)
		{
			auto sum = accumulate(w.cbegin(), w.cend(), 0.);
			transform(w.cbegin(), 
					  w.cend(), 
					  w.begin(), 
					  [&](const auto& el) { return el / sum; });
		}
	}

	template <typename DistanceType>
	void ElasticNet<DistanceType>::UpdateNeurons()
	{
		auto dist_forces = DistForce();
		auto lenght_forces = LenghtForce();

		auto a1 = MatrixMultiplyNum(ElasticNetParameters["alpha"], dist_forces);
		auto a2 = MatrixMultiplyNum(ElasticNetParameters["beta"] * k_, lenght_forces);
		auto final_delta = MatrixesPlus(a1, a2);
		
		auto i = 0u;
		for (auto& neuron : neurons_)
			neuron += final_delta[i++];
	}

	template <typename DistanceType>
	bool ElasticNet<DistanceType>::StopCriteria() const
	{
		// Return True if the algorithm has finished, False otherwise

		return worst_dist_ < ElasticNetParameters["epsilon"] 
			|| iteration_count_ >= ElasticNetParameters["max_num_iter"];
	}

	template <typename DistanceType>
	vector<vector<double>> ElasticNet<DistanceType>::DistForce()
	{
		// Compute the force that minimize the distance between the
		// cities and the neurons.

		auto tmp_weights = MatrixTranspose<double>(weights_);

		vector<vector<double>> result;
		for (auto i = 0; i < neurons_count_; ++i)
		{
			vector<vector<double>> tmp_delta;
			for (auto j = 0 ; j < delta_.size(); ++j)
			{
				tmp_delta.push_back({});
				tmp_delta.back().emplace_back(delta_[j][i][0]);
				tmp_delta.back().emplace_back(delta_[j][i][1]);
			}
			auto t = MatrixMultiply<double>(vector<vector<double>>{tmp_weights[i]}, tmp_delta);
			result.push_back({ t[0][0], t[0][1] } );
		}

		return result;
	}

	template <typename DistanceType>
	vector<vector<double>> ElasticNet<DistanceType>::LenghtForce()
	{
		// Compute the force that minimize the length of the elastic.

		vector<vector<double>> result;
		result.emplace_back(VectorsPlus(VectorsMinus(neurons_[1].V(), VectorsMultiplyNum(2, neurons_[0].V())),
			neurons_[neurons_count_ - 1].V()));

		for (auto i = 1; i < neurons_count_ - 1; ++i)
		{
			result.emplace_back(VectorsPlus(VectorsMinus(neurons_[i + 1].V(), VectorsMultiplyNum(2, neurons_[i].V())),
				neurons_[i - 1].V()));
		}

		result.emplace_back(VectorsPlus(VectorsMinus(neurons_[0].V(), VectorsMultiplyNum(2, neurons_[neurons_count_ - 1].V())),
			neurons_[neurons_count_ - 2].V()));
		
		return result;
	}
}
