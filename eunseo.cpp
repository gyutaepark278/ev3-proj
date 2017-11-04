#include "h_crane.h"
#include "iostream"

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::ultrasonic_sensor ultrasonic_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), ultrasonic_q(ev3dev::INPUT_3), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    float get_distance() 
    {
        return ultrasonic_q.distance_centimeters();
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

    virtual int  get_speed()
    {
        return 100;
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
    void start();
    void find_Obs();
    void put_Obs();
    
};

void Crain::put_Obs(){
    c.set_speed_sp(-1 * get_speed());
    c.run_forever();
}

void Crain::find_Obs(){
    float dist;
    dist=get_distance();
    while(dist > 5){
        dist=get_distance();
        if(dist <= 7){
            b.stop();
            b.set_position_sp(-20);
            b.run_to_rel_pos();
            a.set_speed_sp(get_speed());
            a.set_position_sp(200);
            a.run_to_abs_pos();
            sleep(2);
            
            
            c.set_speed_sp(get_speed());
            c.run_forever();
            sleep(2);
            
            a.set_speed_sp(-1*get_speed());
            a.set_position_sp(0);
            a.run_to_abs_pos();
            break;
        }
    }
}

void Crain::start(){
    b.set_speed_sp(get_speed());
    b.set_position_sp(560);
    b.run_to_abs_pos();
}

int main(){
    int pos;
    Crain crain;
    while(true){
        if(crain.get_touch_pressed()==true){
            crain.start();
            //sleep(2);
            crain.find_Obs();
            //sleep(2);
            crain.start();
            sleep(1);
            crain.put_Obs();
        }
    }
}