#include "controller.h"

Controller::Controller() {
    updatePriority = 4;
}
#include <iostream>
void Controller::Update(double delta) {
    {
        static constexpr double sensitivity = 0.1;
        //add timer to mouse once delta t available
        auto tmp = Input::instance().GetMousePosition();
        mouse_velocity = {(tmp.x - last_mouse.x) * delta * sensitivity, (tmp.y - last_mouse.y) * delta * sensitivity};
        last_mouse = tmp;
    }

    transform->Rotation = glm::quat({0.0,-mouse_velocity.x,0.0}) * transform->Rotation * glm::quat({-mouse_velocity.y,0.0,0.0})   ;
    
    for (auto& a : keyActions) {
        if (Input::instance().GetKey(std::get<0>(a))) {
            (transform->*(std::get<1>(a)))(std::get<2>(a)*delta*speed);
        }
    }


    //

}

void Controller::Init() {
    ConnectTransform(pEntity->getComponent<Transform>());

    last_mouse = Input::instance().GetMousePosition();
    mouse_velocity = {0,0};
}

void Controller::ConnectTransform(Transform* transform) {
    keyActions.clear();

    keyActions.push_back(std::make_tuple(Key_w,&Transform::Forwards,speed ));
    keyActions.push_back(std::make_tuple(Key_a,&Transform::Strafe  ,speed));
    keyActions.push_back(std::make_tuple(Key_s,&Transform::Forwards  ,-speed ));
    keyActions.push_back(std::make_tuple(Key_d,&Transform::Strafe,-speed));
    keyActions.push_back(std::make_tuple(KeyCode::Spacebar,&Transform::Up,speed));
    keyActions.push_back(std::make_tuple(KeyCode::Shift,&Transform::Up,-speed));    

    this->transform = transform;
}