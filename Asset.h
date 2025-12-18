#ifndef ASSET_H
#define ASSET_H

class Asset{

public:

    virtual ~Asset() = default;
    virtual void GetAssetInfo() = 0;

};

#endif
