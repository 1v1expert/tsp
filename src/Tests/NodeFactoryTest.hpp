#pragma once

#include <list>

#include "Helper.hpp"
#include "AbstractTest.hpp"
#include "../Utility/NodeFactory.hpp"

namespace tsp_tests
{
    using std::unique_ptr;
    using std::string;
    using std::shared_ptr;
    using std::weak_ptr;
    using std::stringstream;
    using std::list;

    using std::make_unique;
    using std::make_shared;
    using std::to_string;
    using std::get;

    template<typename NodeDistanceType>
    struct NodeFactoryTests : public AbstractTest
    {
        using NodeSpecialized = tsp::Node<NodeDistanceType>;
        using NodeFactorySpecialized = tsp::NodeFactory<NodeDistanceType>;

        static bool Create() { return true; }

    private:
        static void Fixture_1() {}
        static void Fixture_2() {}
        static void Fixture_3() {}
        static void Fixture_4() {}
        static void Fixture_5() {}
        static void Fixture_6() {}
        static void Fixture_7() {}
        static void Fixture_8() {}
        static void Fixture_9() {}
    };
                                    
    template<>
    struct NodeFactoryTests<int32_t> : public AbstractTest
    {
        using NodeSpecialized = tsp::Node<int32_t>;
        using NodeFactorySpecialized = tsp::NodeFactory<int32_t>;

        static bool Fixture_1();
        static bool Fixture_2();
        static bool Fixture_3();
        static bool Fixture_4();
        static bool Fixture_5();
        static bool Fixture_6();
        static bool Fixture_7();
        static bool Fixture_8();
        static bool Fixture_9();
    };

    template<>
    struct NodeFactoryTests<float> : public AbstractTest
    {
        using NodeSpecialized = tsp::Node<float>;
        using NodeFactorySpecialized = tsp::NodeFactory<float>;

        static bool Fixture_1();
        static bool Fixture_2();
        static bool Fixture_3();
        static bool Fixture_4();
        static bool Fixture_5();
        static bool Fixture_6();
        static bool Fixture_7();
        static bool Fixture_8();
        static bool Fixture_9();
    };


    inline bool NodeFactoryTests<int32_t>::Fixture_1()
    {
        stringstream s1("test1; x; 2; 3; 4; 5; 6; 7;\n"
                        "test2; 1; x; 3; 4; 5; 6; 7;\n"
                        "test3; 1; 2; x; 4; 5; 6; 7;\n"
                        "test4; 1; 2; 3; x; 5; 6; 7;\n"
                        "test5; 1; 2; 3; 4; x; 6; 7;\n"
                        "test6; 1; 2; 3; 4; 5; x; 7;\n"
                        "test7; 1; 2; 3; 4; 5; 6; x;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 7);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 6);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 7);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_2()
    {
        stringstream s1("a; x; 10; 10; 10; 10; 10; 10;\n"
                        "b; 10; x; 10; 10; 10; 10; 10;\n"
                        "c; 10; 10; x; 10; 10; 10; 10;\n"
                        "d; 10; 10; 10; x; 10; 10; 10;\n"
                        "e; 10; 10; 10; 10; x; 10; 10;\n"
                        "f; 10; 10; 10; 10; 10; x; 10;\n"
                        "g; 10; 10; 10; 10; 10; 10; x;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 7);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 6);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) == 10);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_3()
    {
        stringstream s1("test1; x; 2; 3; 4; 5; 6; 7;\n"
                        "test2; 1; x; 3; 4; 5; 6; 7;\n"
                        "test3; 1; 2; x; 4; 5; 6; 7;\n"
                        "test4; 1; 2; 3; x; 5; 6; 7;\n"
                        "test5; 1; 2; 3; 4; x; 6; 7;\n"
                        "test6; 1; 2; 3; 4; 5; x; 7;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 6);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 5);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 6);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_4()
    {
        stringstream s1("test1; x; 2; 3; 4; 5; 6; 7;\n"
                        "test2; 1; x; 3; 4; 5; 6; 7;\n"
                        "test3; 1; 2; x; 4; 5;\n"
                        "test4; 1; 2; 3; x; 5; 6; 7;\n"
                        "test5; 1; 2; 3; 4; x; 6; 7;\n"
                        "test6; 1; 2; 3; 4; 5; x; 7;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 6);
        AssertThat(!node_container->IsFullConnected());

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_5()
    {
        stringstream s1;
        for (auto i = 0; i < 100; ++i)
        {
            s1 << "Node " + to_string(i) << ";";
            for (auto j = 0; j < 100; ++j)
            {
                s1 << (i == j ? "x" : to_string(RandomValue(1, 9999))) << ";";
            }
            s1 << '\n';
        }

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 100);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 99);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 9999);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_6()
    {
        stringstream s1;
        for (auto i = 0; i < 100; ++i)
        {
            s1 << "Some very big stringSome very big stringSome very big string " + to_string(i) << ";";
            for (auto j = 0; j < 100; ++j)
            {
                s1 << (i == j ? "x" : to_string(RandomValue(1, 99999))) << ";";
            }
            s1 << '\n';
        }

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 100);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 99);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 99999);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_7()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            auto size_1 = RandomValue(1, 100);
            auto size_2 = RandomValue(1, 100);

            if (size_2 >= size_1) size_1 += size_2;

            for (auto i = 0; i < size_1; ++i)
            {
                s1 << "test " + to_string(i) << ";";
                for (auto j = 0; j < size_2; ++j)
                    s1 << (i == j ? "x" : to_string(RandomValue(1, 99999))) << ";";
                s1 << '\n';
            }

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container->NodesCount() == size_1);
            AssertThat(!node_container->IsFullConnected());
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_8()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            auto size_1 = RandomValue(1, 100);
            auto size_2 = RandomValue(1, 100);

            if (size_1 > size_2) size_2 += size_1;

            for (auto i = 0; i < size_1; ++i)
            {
                s1 << "test " + to_string(i) << ";";
                for (auto j = 0; j < size_2; ++j)
                    s1 << (i == j ? "x" : to_string(RandomValue(1, 99999))) << ";";
                s1 << '\n';
            }

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container->NodesCount() == size_1);
            AssertThat(node_container->IsFullConnected());
            for (const auto& node : *node_container)
            {
                AssertThat(node->NodesCount() == size_1 - 1);
                for (const auto& tup : *node)
                {
                    AssertThat(!get<0>(tup).expired());
                    AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 99999);
                    AssertThat(get<0>(tup).lock() != node);
                }
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<int32_t>::Fixture_9()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            for (auto i = 0; i < 10000; ++i)
                s1 << RandomValue('0', 'z');

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container != nullptr);
        }

        return HadPassed();
    }


    inline bool NodeFactoryTests<float>::Fixture_1()
    {
        stringstream s1("test1; x; 2.54; 3.15; 4.56; 5.19; 6.45; 7.19;\n"
                        "test2; 1.23; x; 3.39; 4.31; 5.72; 6.64; 7.54;\n"
                        "test3; 1.32; 2.35; x; 4.17; 5.34; 6.35; 7.31;\n"
                        "test4; 1.54; 2.31; 3.87; x; 5.41; 6.15; 7.48;\n"
                        "test5; 1.97; 2.33; 3.98; 4.24; x; 6.36; 7.46;\n"
                        "test6; 1.39; 2.39; 3.36; 4.35; 5.68; x; 7.34;\n"
                        "test7; 1.34; 2.87; 3.39; 4.18; 5.64; 6.68; x;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 7);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 6);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1.f && get<1>(tup) <= 8.f);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_2()
    {
        stringstream s1("a; x; 10.0; 10.0; 10.0; 10.0; 10.0; 10.0;\n"
                        "b; 10.0; x; 10.0; 10.0; 10.0; 10.0; 10.0;\n"
                        "c; 10.0; 10.0; x; 10.0; 10.0; 10.0; 10.0;\n"
                        "d; 10.0; 10.0; 10.0; x; 10.0; 10.0; 10.0;\n"
                        "e; 10.0; 10.0; 10.0; 10.0; x; 10.0; 10.0;\n"
                        "f; 10.0; 10.0; 10.0; 10.0; 10.0; x; 10.0;\n"
                        "g; 10.0; 10.0; 10.0; 10.0; 10.0; 10.0; x;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 7);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 6);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) == 10.f);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_3()
    {
        stringstream s1("test1; x; 2.5; 3.5; 4.5; 5.5; 6.5; 7.5;\n"
                        "test2; 1.5; x; 3.5; 4.5; 5.5; 6.5; 7.5;\n"
                        "test3; 1.5; 2.5; x; 4.5; 5.5; 6.5; 7.5;\n"
                        "test4; 1.5; 2.5; 3.5; x; 5.5; 6.5; 7.5;\n"
                        "test5; 1.5; 2.5; 3.5; 4.5; x; 6.5; 7.5;\n"
                        "test6; 1.5; 2.5; 3.5; 4.5; 5.5; x; 7.5;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 6);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 5);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1 && get<1>(tup) <= 7.f);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_4()
    {
        stringstream s1("test1; x; 2.2; 3.2; 4.2; 5.2; 6.2; 7.2;\n"
                        "test2; 1.2; x; 3.2; 4.2; 5.2; 6.2; 7.2;\n"
                        "test3; 1.2; 2.2; x; 4.2; 5.2;\n"
                        "test4; 1.2; 2.2; 3.2; x; 5.2; 6.2; 7.2;\n"
                        "test5; 1.2; 2.2; 3.2; 4.2; x; 6.2; 7.2;\n"
                        "test6; 1.2; 2.2; 3.2; 4.2; 5.2; x; 7.2;\n");

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 6);
        AssertThat(!node_container->IsFullConnected());

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_5()
    {
        stringstream s1;
        for (auto i = 0; i < 100; ++i)
        {
            s1 << "Node " + to_string(i) << ";";
            for (auto j = 0; j < 100; ++j)
            {
                s1 << (i == j ? "x" : to_string(RandomValue(1.f, 9999.f))) << ";";
            }
            s1 << '\n';
        }

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 100);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 99);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1.f && get<1>(tup) <= 9999.f);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_6()
    {
        stringstream s1;
        for (auto i = 0; i < 100; ++i)
        {
            s1 << "Some very big stringSome very big stringSome very big string " + to_string(i) << ";";
            for (auto j = 0; j < 100; ++j)
            {
                s1 << (i == j ? "x" : to_string(RandomValue(1.f, 99999.f))) << ";";
            }
            s1 << '\n';
        }

        auto node_container = NodeFactorySpecialized::Create(s1);
        AssertThat(node_container->NodesCount() == 100);
        AssertThat(node_container->IsFullConnected());
        for (const auto& node : *node_container)
        {
            AssertThat(node->NodesCount() == 99);
            for (const auto& tup : *node)
            {
                AssertThat(!get<0>(tup).expired());
                AssertThat(get<1>(tup) >= 1.f && get<1>(tup) <= 99999.f);
                AssertThat(get<0>(tup).lock() != node);
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_7()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            auto size_1 = RandomValue(1, 100);
            auto size_2 = RandomValue(1, 100);

            if (size_2 >= size_1) size_1 += size_2;

            for (auto i = 0; i < size_1; ++i)
            {
                s1 << "test " + to_string(i) << ";";
                for (auto j = 0; j < size_2; ++j)
                    s1 << (i == j ? "x" : to_string(RandomValue(1.f, 99999.f))) << ";";
                s1 << '\n';
            }

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container->NodesCount() == size_1);
            AssertThat(!node_container->IsFullConnected());
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_8()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            auto size_1 = RandomValue(1, 100);
            auto size_2 = RandomValue(1, 100);

            if (size_1 > size_2) size_2 += size_1;

            for (auto i = 0; i < size_1; ++i)
            {
                s1 << "test " + to_string(i) << ";";
                for (auto j = 0; j < size_2; ++j)
                    s1 << (i == j ? "x" : to_string(RandomValue(1.f, 99999.f))) << ";";
                s1 << '\n';
            }

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container->NodesCount() == size_1);
            AssertThat(node_container->IsFullConnected());
            for (const auto& node : *node_container)
            {
                AssertThat(node->NodesCount() == size_1 - 1);
                for (const auto& tup : *node)
                {
                    AssertThat(!get<0>(tup).expired());
                    AssertThat(get<1>(tup) >= 1.f && get<1>(tup) <= 99999.f);
                    AssertThat(get<0>(tup).lock() != node);
                }
            }
        }

        return HadPassed();
    }

    inline bool NodeFactoryTests<float>::Fixture_9()
    {
        for (auto repeat = 0; repeat < 10; ++repeat)
        {
            stringstream s1;
            for (auto i = 0; i < 10000; ++i)
                s1 << RandomValue('0', 'z');

            auto node_container = NodeFactorySpecialized::Create(s1);
            AssertThat(node_container != nullptr);
        }

        return HadPassed();
    }
}
