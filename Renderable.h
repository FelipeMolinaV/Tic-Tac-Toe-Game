#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable{

public:

    virtual void Render() = 0;
    virtual void SetLayer(int layer) = 0;
    virtual int GetLayer() = 0;

    virtual void SetAlpha(int alpha) = 0;
    virtual int GetAlpha() = 0;

    virtual void SetVisibleState(bool state) = 0;
    virtual bool GetVisibleState() = 0;

};


#endif
