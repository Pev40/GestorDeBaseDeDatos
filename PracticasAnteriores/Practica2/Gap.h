#ifndef __GAP_H__
#define __GAP_H__
class Gap
{
private:
    int longitud;
public:
    Gap(int);
    ~Gap();
};

Gap::Gap(int longitud) {
        this->longitud = longitud;
    }

Gap::~Gap()
{
}

#endif