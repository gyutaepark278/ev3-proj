#include "h_crane.h"
#include <iostream>

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2),a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    int m_pos;
    
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

    virtual int  get_speed()
    {
        return 300;
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
    void position_Test();
};

void Crain::position_Test(){
    /*
    b.set_speed_sp(get_speed());
    b.set_position_sp(200);
    b.run_to_abs_pos();
    sleep(3);
    m_pos=b.position();
    b.set_position_sp(560);
    b.run_to_abs_pos();
    sleep(3);
    b.set_position_sp(m_pos);
    b.run_to_abs_pos();
    */
    b.set_speed_sp(get_speed());
    b.set_position_sp(200);
    b.run_to_abs_pos();
    sleep(3);
    c.set_speed_sp(get_speed());
    c.set_position_sp(0);
    c.run_to_abs_pos();
    sleep(2);
    c.set_position_sp(-50);
    c.run_to_abs_pos();
    sleep(2);
    c.set_position_sp(50);
    c.run_to_abs_pos();
    sleep(2);
    c.set_position_sp(-100);
    c.run_to_abs_pos();
    
    /*
    while(true){
        m_pos=b.position();
        if(m_pos=100){
            b.stop();
        }
    }
    */
    
    
    
}



int main(){     
    Crain crain;
    while(true){
        if(crain.get_touch_pressed()==true){ 
            
        
        crain.position_Test();
        }
    }
}