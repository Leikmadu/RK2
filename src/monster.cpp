#include "monster.hpp"

// Slime operators
bool Slime::IntrinsicState::operator<(IntrinsicState const& state) const
{
    if (viscosity < state.viscosity)
        return true;
    else if (viscosity > state.viscosity)
        return false;
    else
        return transparency < state.transparency;
}

Slime::Slime(IntrinsicState const& state) : state_(state) {}

void Slime::Print(MonsterContext const& context) const
{
    std::cout << "----- Slime -----" << std::endl;
    std::cout << "HP           : " << context.hp << std::endl;
    std::cout << "Position     : (" << context.posX << ", " << context.posY << ")" << std::endl;
    std::cout << "Viscosity    : " << state_.viscosity << std::endl;
    std::cout << "Transparency : " << state_.transparency << std::endl;
    std::cout << "-----------------" << std::endl;
}

// Goblin operators
bool Goblin::IntrinsicState::operator<(IntrinsicState const& state) const
{
    if (angerDegree < state.angerDegree)
        return true;
    else if (angerDegree > state.angerDegree)
        return false;
    else
        return uglinessDegree < state.uglinessDegree;
}

Goblin::Goblin(IntrinsicState const& state) : state_(state) {}

void Goblin::Print(MonsterContext const& context) const
{
    std::cout << "----- Goblin -----" << std::endl;
    std::cout << "HP             : " << context.hp << std::endl;
    std::cout << "Position       : (" << context.posX << ", " << context.posY << ")" << std::endl;
    std::cout << "AngerDegree    : " << state_.angerDegree << std::endl;
    std::cout << "UglinessDegree : " << state_.uglinessDegree << std::endl;
    std::cout << "------------------" << std::endl;
}

// Dragon operators
bool Dragon::IntrinsicState::operator<(IntrinsicState const& state) const
{
    if (height < state.height)
        return true;
    else if (height > state.height)
        return false;
    else
        return firePower < state.firePower;
}

Dragon::Dragon(IntrinsicState const& state) : state_(state) {}

void Dragon::Print(MonsterContext const& context) const
{
    std::cout << "----- Dragon -----" << std::endl;
    std::cout << "HP        : " << context.hp << std::endl;
    std::cout << "Position  : (" << context.posX << ", " << context.posY << ")" << std::endl;
    std::cout << "Height    : " << state_.height << std::endl;
    std::cout << "FirePower : " << state_.firePower << std::endl;
    std::cout << "------------------" << std::endl;
}

// MonsterPool implementation
template <typename MonsterType>
MonsterType const& MonsterPool::GetImpl_(
    std::map<typename MonsterType::IntrinsicState, MonsterType>& pool,
    typename MonsterType::IntrinsicState const& state)
{
    auto iter = pool.find(state);
    if (iter == std::end(pool))
    {
        iter = pool.insert(std::make_pair(state, MonsterType(state))).first;
    }
    return iter->second;
}

Slime const& MonsterPool::GetSlime(Slime::IntrinsicState const& state)
{
    return GetImpl_(slimePool_, state);
}

Goblin const& MonsterPool::GetGoblin(Goblin::IntrinsicState const& state)
{
    return GetImpl_(goblinPool_, state);
}

Dragon const& MonsterPool::GetDragon(Dragon::IntrinsicState const& state)
{
    return GetImpl_(dragonPool_, state);
}

void PrintMonsterInfo(MonsterInfo const& monsterInfo)
{
    monsterInfo.monster.Print(monsterInfo.context);
}

int main()
{
    MonsterPool monsterPool;
    std::vector<MonsterInfo> monsterInfoList;
    
    monsterInfoList.push_back({ monsterPool.GetSlime({ 6, 3 }), { 50, 0, 0 } });
    monsterInfoList.push_back({ monsterPool.GetSlime({ 6, 3 }), { 30, 1, 2 } });
    monsterInfoList.push_back({ monsterPool.GetSlime({ 1, 2 }), { 40, 2, -1 } });

    monsterInfoList.push_back({ monsterPool.GetGoblin({ 7, 5 }), { 80, 9, -3 } });
    monsterInfoList.push_back({ monsterPool.GetGoblin({ 5, 8 }), { 70, -5, -3 } });
    monsterInfoList.push_back({ monsterPool.GetGoblin({ 5, 8 }), { 90, 7, 0 } });

    monsterInfoList.push_back({ monsterPool.GetDragon({ 10, 12 }), { 200, 2, 11 } });
    monsterInfoList.push_back({ monsterPool.GetDragon({ 10, 12 }), { 400, 0, 9 } });
    monsterInfoList.push_back({ monsterPool.GetDragon({ 10, 12 }), { 350, 5, 1 } });

    PrintMonsterInfo(monsterInfoList[4]);
    monsterInfoList[4].context.hp -= 10;
    monsterInfoList[4].context.posX += 3;
    monsterInfoList[4].context.posY -= 1;
    PrintMonsterInfo(monsterInfoList[4]);

    PrintMonsterInfo(monsterInfoList[8]);
    monsterInfoList[8].context.hp -= 30;
    monsterInfoList[8].context.posX += 2;
    monsterInfoList[8].context.posY -= 7;
    PrintMonsterInfo(monsterInfoList[8]);
    
    return 0;
}
