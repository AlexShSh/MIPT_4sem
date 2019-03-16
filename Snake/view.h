#pragma once

class View
{
public:
    void virtual draw() = 0;
    void virtual run()  = 0;
    virtual ~View()     = 0; 

    static View* get();
    static View* inst;
};

