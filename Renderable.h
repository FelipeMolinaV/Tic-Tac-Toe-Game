#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable{

public:

    virtual void Render() = 0;
    virtual void SetLayer(int layer) = 0;
    virtual int GetLayer() = 0;

};


#endif
