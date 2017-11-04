#include "h_crane.h"
#include <iostream>


class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::ultrasonic_sensor ultrasonic_q;
    ev3dev::motor a;//up/down
    ev3dev::motor b;//right/left
    ev3dev::motor c;//hold/lose
    

public:
    // Hardware Configuration
    Crain():m_speed(0), ultrasonic_q(ev3dev::INPUT_3), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    int m_pos;
    
    float get_distance() 
    {
        return ultrasonic_q.distance_centimeters();//With Color, the sensor evaluates the color of an object and outputs one of the following values:
    }
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    virtual bool get_down()
    {
        return m_down;
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int  get_time()
    {
        return 30;
    }
    
    virtual int  get_speed()
    {
        return 100; //여길만지면 빨라지고 시간단축 할듯!
    }

    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;
    }
    
    virtual void set_left(bool val)
    {
        m_left = val;
    }
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;
    }
public:
    void example_code();
};

void Crain::example_code()
{
    float dist;
    b.set_speed_sp(get_speed()); //b= r/l
    
    b.set_position_sp(560);
    b.run_to_abs_pos();
    dist=get_distance();
    while(dist > 3){
        dist=get_distance();
        if(dist <= 7){
            b.stop();
            // b.set_position_sp(-10);
            // b.run_to_rel_pos();
            // m_pos=b.position();
            a.set_speed_sp(get_speed());
            // a.set_position_sp(200);
            // a.run_to_abs_pos();
            a.run_forever();
        }
    a.stop();
    }
    /*
    a.set_speed_sp(-1*get_speed());
    a.set_position_sp(0);
    a.run_to_abs_pos();
    }

    if(get_distance() <= 20){
        
    }
    
    while(true)
    {
        
        {
            b.stop();
            if(get_distance() >= 7)
            {
                a.set_speed_sp(get_speed());
                a.run_forever();
            }
            a.stop();
            sleep(2);
            
            c.set_speed_sp(get_speed());
            c.set_position_sp(0);
            c.run_to_abs_pos();
            sleep(2);
            
            a.set_speed_sp(-1*get_speed());
            a.set_position_sp(0);
            a.run_to_abs_pos();
            sleep(2);
            
        }
        
        else
        {
            
        }
    }
    */
}

int main()
{     
    Crain crain;
    while(true){//ev3안에서 니가 반복할 수 있는 것을 반복해라는거라서 이거 바꿔야함;;;;기다리게 만들어야함 
        //모터가 동작이 끝났는지 기다려야함... 어떻게 할 수 있을까... 너 얼마만큼 기다려야해가 들어가있어야함 
        if(crain.get_touch_pressed()==true){ 
            
        crain.example_code();
  
        }
    }
}