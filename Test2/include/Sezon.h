#ifndef SEZON_H
#define SEZON_H


class Sezon
{
    public:
        Sezon();
        virtual ~Sezon();

        int getSezonId() { return sezonId; }
        void getSezonId(int val) { sezonId = val; }

    protected:

    private:
        int sezonId;
};

#endif // SEZON_H
