struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    Image(const char *filename);    
    void SetSizeX(unsigned long i){sizeX = i;}
    unsigned long GetSizeX(unsigned long i){return sizeX;}
    unsigned long GetSizeY(unsigned long i){return sizeY;}
    void SetSizeY(unsigned long i){sizeY = i;}
};
