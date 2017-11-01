#include "h_crane.h"

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::color_sensor color_q;
    ev3dev::motor a;//up/down
    ev3dev::motor b;//right/left
    ev3dev::motor c;//hold/lose
    

public:
    // Hardware Configuration
    Crain():m_speed(0), color_q(ev3dev::INPUT_3), touch_q(ev3dev::INPUT_2), a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)//input3을 만들어야하나요?
    {
        
    }
    
    int m_speed;
    

    int get_color() 
    {
        return color_q.color();//With Color, the sensor evaluates the color of an object and outputs one of the following values:
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
    while(get_escape() == false)
    {
        set_down(ev3dev::button::down.pressed());
        set_up(ev3dev::button::up.pressed());
        set_right(ev3dev::button::right.pressed());
        set_left(ev3dev::button::left.pressed());
        set_escape(ev3dev::button::back.pressed());
        set_enter(ev3dev::button::enter.pressed());
        
        for(int i = 0; i < 3; i++ )//장애물 3개
        {
            b.set_speed_sp(get_speed()); //b= r/l
            b.set_position_sp(560);
            b.run_to_abs_pos();
            
            if(b.position_sp() == 560)
            {
                a.set_speed_sp(get_speed());
                a.set_position_sp(300);
                a.run_to_abs_pos();
                if(a.position_sp()==300)
                    {
                        c.set_speed_sp(get_speed());
                        c.set_position_sp(80);
                        c.run_to_abs_pos();
                    }
            }
            
            if(get_color() != 6)//완성되면 != white color(6)으로 바꿔주자!
            {
                b.stop(); //if color sensor find black color, then stop
                //b position memory
                a.set_speed_sp(get_speed());//일정하게 내려가야함
                c.set_speed_sp(get_speed());//잡아주고,(대신 계속 돌아가면 rotate되니까 일정한 값을 다시 시도해보자
                a.set_speed_sp(-1*get_speed());//올라가고
                b.set_speed_sp(-1* get_speed());//finish point까지 가야함.
                //b position memory자리로 돌아감
            }
        }
        
    }

    a.stop();
    b.stop();
    c.stop();
}

int main()
{     
    Crain crain;
    while(true){
        if(crain.get_touch_pressed()==true){ 
            
        crain.example_code();  
  
        }
    }
}