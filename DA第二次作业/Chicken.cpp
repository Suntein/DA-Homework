#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name =nullptr;//nullptr=null
    public:
        Chicken& operator=(const Chicken &other){
            if(this != & other) {
                delete [] name;
                age=other.age;
                if(other.name!=nullptr){
                    name = new char(strlen(other.name)+1);
                    strcpy(name,other.name); 
                }else{
                    name=nullptr;
                }
            }    
            return *this;
        } 
        Chicken(){};
        Chicken(int _age) : age(_age) {};
        Chicken(int _age, const char *_name) : age(_age) 
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        };
        ~Chicken()
        {
            if (name != nullptr)
                delete[] name;
        }
        void setAge(int _age)
        {
            age = _age;
        }
        void setName(const char *_name)
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        }

        const char *getName() const
        {
            return name;
        }

        const int &getAge() const
        {
            return age;
        }
};

int main(){
    Chicken kun (26,"jinitaimei");
    Chicken mm;
    mm=kun;
    std::cout<<mm.getName()<<std::endl;
    return 0;
}