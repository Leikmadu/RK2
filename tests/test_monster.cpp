#include <gtest/gtest.h>
#include "monster.hpp"

TEST(MonsterPoolTest, FlyweightPatternWorks)
{
    MonsterPool pool;
    
    Slime::IntrinsicState state1{6, 3};
    Slime::IntrinsicState state2{6, 3};
    Slime::IntrinsicState state3{1, 2};
    
    const Slime& slime1 = pool.GetSlime(state1);
    const Slime& slime2 = pool.GetSlime(state2);
    const Slime& slime3 = pool.GetSlime(state3);
    
    EXPECT_EQ(&slime1, &slime2);
    EXPECT_NE(&slime1, &slime3);
}
