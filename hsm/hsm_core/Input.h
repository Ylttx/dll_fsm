#ifndef INPUT_H
#define INPUT_H

namespace hsm {

class Input {
public:
    Input(int type, void *p_data = nullptr) {
        m_type = type;
        m_data = p_data;
    }
 
    ~Input() {}

    int getType(void) const { return m_type; }
 
private:
    int m_type;
    void *m_data;
};

} // namespace hsm

#endif