#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <iostream>
#include <map>
#include <vector>

struct MonsterContext
{
    int hp;
    int posX, posY;
};

class Monster
{
public:
    virtual ~Monster() = default;
    virtual void Print(MonsterContext const& context) const = 0;
};

class Slime : public Monster
{
public:
    struct IntrinsicState
    {
        bool operator<(IntrinsicState const& state) const;
        int viscosity;
        int transparency;
    };

    explicit Slime(IntrinsicState const& state);
    void Print(MonsterContext const& context) const override;

private:
    IntrinsicState state_;
};

class Goblin : public Monster
{
public:
    struct IntrinsicState
    {
        bool operator<(IntrinsicState const& state) const;
        int angerDegree;
        int uglinessDegree;
    };

    explicit Goblin(IntrinsicState const& state);
    void Print(MonsterContext const& context) const override;

private:
    IntrinsicState state_;
};

class Dragon : public Monster
{
public:
    struct IntrinsicState
    {
        bool operator<(IntrinsicState const& state) const;
        int height;
        int firePower;
    };

    explicit Dragon(IntrinsicState const& state);
    void Print(MonsterContext const& context) const override;

private:
    IntrinsicState state_;
};

class MonsterPool
{
public:
    Slime const& GetSlime(Slime::IntrinsicState const& state);
    Goblin const& GetGoblin(Goblin::IntrinsicState const& state);
    Dragon const& GetDragon(Dragon::IntrinsicState const& state);

private:
    template <typename MonsterType>
    static MonsterType const& GetImpl_(
        std::map<typename MonsterType::IntrinsicState, MonsterType>& pool,
        typename MonsterType::IntrinsicState const& state);

    std::map<Slime::IntrinsicState, Slime> slimePool_;
    std::map<Goblin::IntrinsicState, Goblin> goblinPool_;
    std::map<Dragon::IntrinsicState, Dragon> dragonPool_;
};

struct MonsterInfo
{
    Monster const& monster;
    MonsterContext context;
};

void PrintMonsterInfo(MonsterInfo const& monsterInfo);

#endif
