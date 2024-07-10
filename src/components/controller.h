#include <vector>

#include "component.h"
#include "input.h"
#include "transform.h"

class Controller : public Component {

    Mouse last_mouse = {0,0}, mouse_velocity = {0,0};
    
    double speed = 2.0;
    Transform* transform = nullptr;

    std::vector<std::tuple<KeyCode,void(Transform::*)(double),double>> keyActions;

    public:
    Controller();
    ~Controller();
    void ConnectTransform(Transform* transform);
    void Update(double delta) override;
    void Init() override;
};