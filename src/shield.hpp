#ifndef SHIELD_HPP
#define SHIELD_HPP

namespace Object {
    
class Shield
{

public:
    Shield(bool active, int energy);
    ~Shield();
private:
    bool m_active;
    int m_energy;
};

} // namespace Object

#endif