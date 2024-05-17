#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;


void Input_str(string text)
{
    fstream f;
    f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::app | ios::binary);
    const char* charArray = text.c_str(); // Преобразование строки в массив символов
    int size = text.size() + 1; // Размер строки включая нулевой символ
    f.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Записываем размер строки
    f.write(charArray, size); // Записываем содержимое строки
    f.close();
}

string Output_str(fstream &f)
{

            int readSize;
            f.read(reinterpret_cast<char*>(&readSize), sizeof(readSize)); // Чтение размера строки

            // Выделение памяти и чтение содержимого строки
            char* buffer = new char[readSize];
            f.read(buffer, readSize);

            string readString(buffer); // Преобразование массива символов обратно в строку

            // Освобождение памяти
            delete[] buffer;
            return readString;

}

class Products
{
    private:
    public:
        static inline int count = 0;
        int read_type;
        static inline Products* arr[100];
        static inline int read_count = 0;
        int typeP; // Products - 0; Furniture - 10; Clothes - 20; Shirts - 100; Belt - 200; Chair - 300; Table - 400;
        int cost;
        string name;
        string descr;

        virtual void input()
        {
            

            fstream f;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::app | ios::binary);   
            f.write(reinterpret_cast<char*>(&this->typeP), sizeof(int));  
            f.write(reinterpret_cast<char*>(&this->cost), sizeof(int));
            f.close();
            Input_str(this->name);
            Input_str(this->descr);
        }    

        Products()
        {

        }

        Products(int cost, string name, string descr)
        {
            this->cost=cost;
            this->name=name;
            this->descr=descr;
            this->typeP=0;
            arr[count] = this;
            count++;
        }

        ~Products()
        {
            
        }

        virtual void print()
        {
            cout<<"cost = "<<this->cost<<endl;
            cout<<"name = "<<this->name<<endl;
            cout<<"describe = "<<this->descr<<endl;
        }

        virtual void read(int i, fstream & f)
        {   
            arr[i] = new Products();
            f.read(reinterpret_cast<char*>(&arr[i]->cost), sizeof(int));
            Output_str(f);
            Output_str(f);
            arr[i]->print(); 
        }    

        virtual void AddThings(int thing_count)
        {

        }

        virtual void TotalCost()
        {

        }


};

class Furniture: public Products
{
    private:
    public:
        int size_of_furniture;
        string material_of_furniture;
        string color_of_furniture;

        virtual void input()
        {
            Products::input();
            fstream f;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::app | ios::binary); 
            f.write(reinterpret_cast<char*>(&this->size_of_furniture), sizeof(int));
            f.close();
            Input_str(this->material_of_furniture);
            Input_str(this->color_of_furniture);
        } 

        Furniture(): Products()
        {
            
        }

        Furniture(int cost, string name, string descr, int size_of_furniture, string material_of_furniture, string color_of_furniture): Products(cost, name, descr), size_of_furniture(size_of_furniture), material_of_furniture(material_of_furniture), color_of_furniture(color_of_furniture)
        {
            this->size_of_furniture=size_of_furniture;
            this->material_of_furniture=material_of_furniture;
            this->color_of_furniture=color_of_furniture; 
            this->typeP=10;
        }

        ~Furniture()
        {

        }

        virtual void print()
        {
            Products::print();
            cout<<"size of furniture = "<<this->size_of_furniture<<endl;
            cout<<"material of furniture = "<<this->material_of_furniture<<endl;
            cout<<"color of furniture = "<<this->color_of_furniture<<endl;
        }    

};

class Clothes: public Products
{
    private:
    public:
        int size_of_clothes;
        string sex;

        virtual void input()
        {
            Products::input();
            fstream f;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::app | ios::binary);           
            f.write(reinterpret_cast<char*>(&this->size_of_clothes), sizeof(int));
            f.close();
            Input_str(this->sex);
        } 

        Clothes(): Products()
        {
            
        }

        Clothes(int cost, string name, string descr, int size_of_clothes, string sex): Products(cost, name, descr), size_of_clothes(size_of_clothes), sex(sex)
        {
            this->size_of_clothes=size_of_clothes;
            this->sex=sex;
            this->typeP=20;
        }

        ~Clothes()
        {
            
        }

        virtual void print()
        {
            Products::print();
            cout<<"size of clothes = "<<this->size_of_clothes<<endl;
            cout<<"sex = "<<this->sex<<endl;
        }  
};

class Shirts: public Clothes
{
    private:
    public:
        string color_of_shirts;
        string material_of_shirts;

        virtual void input()
        {
            Clothes::input();
            Input_str(this->color_of_shirts);
            Input_str(this->material_of_shirts);
        } 

        Shirts(): Clothes()
        {
            
        }

        Shirts(int cost, string name, string descr, int size_of_clothes, string sex, string color_of_shirts, string material_of_shirts): Clothes(cost, name, descr, size_of_clothes, sex), material_of_shirts(material_of_shirts), color_of_shirts(color_of_shirts)
        {
            this->color_of_shirts=color_of_shirts;
            this->material_of_shirts=material_of_shirts;
            this->typeP=100;
        }

        ~Shirts()
        {
            
        }

        void print()
        {
            Clothes::print();
            cout<<"color of shirts = "<<this->color_of_shirts<<endl;
            cout<<"material of shirts = "<<this->material_of_shirts<<endl;
        }  
        
        void read(int i, fstream & f)
        {
            int t_cost;
            string t_name;
            string t_descr;
            int t_size;
            string t_sex;
            string t_color;
            string t_material;
            f.read(reinterpret_cast<char*>(&t_cost), sizeof(int));
            t_name = Output_str(f);
            t_descr = Output_str(f);
            f.read(reinterpret_cast<char*>(&t_size), sizeof(int));
            t_sex = Output_str(f);
            t_color = Output_str(f);
            t_material = Output_str(f);
            arr[i] = new Shirts(t_cost, t_name, t_descr, t_size, t_sex, t_color, t_material);
            arr[i]->print();
        } 
};

class Belt: public Clothes
{
    private:
    public:
        string is_double;

        virtual void input()
        {
            Clothes::input();
            Input_str(this->is_double);
        } 

        Belt(): Clothes()
        {
            
        }

        Belt(int cost, string name, string descr, int size_of_clothes, string sex, string is_double): Clothes(cost, name, descr, size_of_clothes, sex), is_double(is_double)
        {
            this->is_double=is_double;
            this->typeP=200;
        }

        ~Belt()
        {
            
        }

        void print()
        {
            Clothes::print();
            cout<<"belt is double = "<<this->is_double<<endl;
        }  

        void read(int i, fstream & f)
        {
            int b_cost;
            string b_name;
            string b_descr;
            int b_size;
            string b_sex;
            string b_is_double;
            f.read(reinterpret_cast<char*>(&b_cost), sizeof(int));
            b_name = Output_str(f);
            b_descr = Output_str(f);
            f.read(reinterpret_cast<char*>(&b_size), sizeof(int));
            b_sex = Output_str(f);
            b_is_double = Output_str(f);
            arr[i] = new Belt(b_cost, b_name, b_descr, b_size, b_sex, b_is_double);
            arr[i]->print();
        }
};

class Chair: public Furniture
{
    private:
    public:
        string is_back;
        string is_soft;

        virtual void input()
        {
            Furniture::input();
            Input_str(this->is_back);
            Input_str(this->is_soft);
        } 

        Chair(): Furniture()
        {
            
        }

        Chair(int cost, string name, string descr, int size_of_furniture, string material_of_furniture, string color_of_furniture, string is_back, string is_soft): Furniture(cost, name, descr, size_of_furniture, material_of_furniture, color_of_furniture), is_back(is_back), is_soft(is_soft)
        {
            this->is_back=is_back;
            this->is_soft=is_soft;
            this->typeP=300;
        }

        ~Chair()
        {
            
        }

        void print()
        {
            Furniture::print();
            cout<<"Chair is back = "<<this->is_back<<endl;
            cout<<"Chair is soft = "<<this->is_soft<<endl;
        }  

        void read(int i, fstream & f)
        {
            int c_cost;
            string c_name;
            string c_descr;
            int c_size;
            string c_color;
            string c_material;
            string c_is_back;
            string c_is_soft;
            f.read(reinterpret_cast<char*>(&c_cost), sizeof(int));
            c_name = Output_str(f);
            c_descr = Output_str(f);
            f.read(reinterpret_cast<char*>(&c_size), sizeof(int));
            c_material = Output_str(f);
            c_color = Output_str(f);
            c_is_back = Output_str(f);
            c_is_soft = Output_str(f);
            arr[i] = new Chair(c_cost, c_name, c_descr, c_size, c_material, c_color, c_is_back, c_is_soft);
            arr[i]->print();
        }
};

class Table: public Furniture   
{
    private:
    public:
        string is_mutable;
        virtual void input()
        {
            Furniture::input();
            Input_str(this->is_mutable);
        } 

        Table(): Furniture()
        {
            
        }

        Table(int cost, string name, string descr, int size_of_furniture, string material_of_furniture, string color_of_furniture, string is_mutable): Furniture(cost, name, descr, size_of_furniture, material_of_furniture, color_of_furniture), is_mutable(is_mutable)
        {
            this->is_mutable=is_mutable;
            this->typeP=400;
        }

        ~Table()
        {

        }

        void print()
        {
            Furniture::print();
            cout<<"Table is mutable = "<<this->is_mutable<<endl;
        }

        void read(int i, fstream & f)
        {
            int ta_cost;
            string ta_name;
            string ta_descr;
            int ta_size;
            string ta_color;
            string ta_material;
            string ta_is_mutable;
            f.read(reinterpret_cast<char*>(&ta_cost), sizeof(int));
            ta_name = Output_str(f);
            ta_descr = Output_str(f);
            f.read(reinterpret_cast<char*>(&ta_size), sizeof(int));
            ta_material = Output_str(f);
            ta_color = Output_str(f);
            ta_is_mutable = Output_str(f);
            arr[i] = new Table(ta_cost, ta_name, ta_descr, ta_size, ta_material, ta_color, ta_is_mutable);
            arr[i]->print();
        }
};


void BigMac(int Big_count)
{
    for (int i=0; i<Big_count; i++)
    {
        (*Products::arr[i]).input();
    }
}

class Basket: public Products
{
    public:
        int thing_in_basket_count;
        static inline Products* arr_of_basket[100];
        int total_cost;
        int basket_count=0;
        void AddThings()
        {
            int thing_count;
            cout<<endl;
            cout<<"Enter the number of thing"<<endl;
            cin>>thing_count;
            arr_of_basket[basket_count] = Products::arr[thing_count];
            basket_count++;            
            for (int i=thing_count; i<read_count-1; i++)
            {
                Products::arr[i] = Products::arr[i+1];
            }
            read_count--;
            
            
            cout<<"SHOP"<<endl;
            fstream f;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::out | ios::binary);
            f.close();
            BigMac(read_count);
            cout<<endl;

            read_count = 0;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::in | ios::binary);
            while (f.read(reinterpret_cast<char*>(&read_type), sizeof(int))) 
            {
                switch (read_type)
                {
                
                case 100:
                    {
                        cout<<read_count<<") Shirt:"<<endl;
                        cout<<endl;
                        Products::arr[read_count] = new Shirts();
                        Products::arr[read_count]->read(read_count, f);
                        cout<<endl;
                        cout<<endl;
                        break;
                    }

                case 200:
                    {
                        cout<<read_count<<") Belt:"<<endl;
                        cout<<endl;
                        Products::arr[read_count] = new Belt();
                        Products::arr[read_count]->read(read_count, f);
                        cout<<endl;
                        cout<<endl;
                        break;
                    }

                case 300:
                    {
                        cout<<read_count<<") Chair:"<<endl;
                        cout<<endl;
                        Products::arr[read_count] = new Chair();
                        Products::arr[read_count]->read(read_count, f);
                        cout<<endl;
                        cout<<endl;
                        break;
                    }

                case 400:
                    {
                        cout<<read_count<<") Table:"<<endl;
                        cout<<endl;
                        Products::arr[read_count] = new Table();
                        Products::arr[read_count]->read(read_count, f);
                        cout<<endl;
                        cout<<endl;
                        break;
                    }
                        
                
                }

                read_count++;
            }
            f.close();
            Products::count = 0;          
        }


        void OpenBasket()
        {
            cout<<endl;
            cout<<"BASKET"<<endl;
            for (int i=0; i<basket_count; i++)
                {
                    switch (arr_of_basket[i]->typeP)
                    {
                    case 100:
                        cout<<i<<") Shirt:"<<endl;
                        break;
                    
                    case 200:
                        cout<<i<<") Belt:"<<endl;
                        break;
                    
                    case 300:
                        cout<<i<<") Chair:"<<endl;
                        break;
                    
                    case 400:
                        cout<<i<<") Table:"<<endl;
                        break;
                    }
                    cout<<endl;
                    arr_of_basket[i]->print();
                    cout<<endl;
                }
            cout<<endl;
        }

        void TotalCost()
        {
            cout<<endl;
            total_cost = 0;
            for (int i=0; i<basket_count; i++)
                {
                    total_cost+=arr_of_basket[i]->cost;
                }
            cout<<"Total cost: "<<total_cost<<endl;
            cout<<endl;
        }

        void RemoveThings()
        {
            cout<<endl;
            cout<<"Enter the number of thing"<<endl;
            cin>>thing_in_basket_count;
            Products::arr[read_count] = arr_of_basket[thing_in_basket_count];
            for (int i=thing_in_basket_count; i<basket_count-1; i++)
                {
                    arr_of_basket[i]=arr_of_basket[i+1];
                }
            basket_count--;
            read_count++;
            fstream f;
            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::out | ios::binary);
            f.close();
            BigMac(read_count);
            cout<<endl;
        }

        void Buy()
        {
            for (int i=0; i<basket_count; i++)
            {
                delete(arr_of_basket[i]);
            }
            basket_count = 0;
        }

};

int main()
{
    int mode_changer;
    int product_changer;
    int furtiture_changer;
    int clothes_changer;
    int read_type;
    int readSize;
    Products* arr_of_basket[100];
    int basket_count=0;
    while (mode_changer!=5)

        {
            cout<<"1. Stock"<<endl;
            cout<<"2. Shop"<<endl;
            cout<<"3. Basket"<<endl;
            cout<<"4. Clear"<<endl;
            cout<<"5. Exit"<<endl;
            cin>>mode_changer;
            switch (mode_changer)

                {
                    case 1:

                        {
                            // int password;
                            // while (true) 
                            // {
                            //     system("cls");
                            //     cout<<"Enter the password"<<endl;                //PASSWORD!!!
                            //     cin>>password;
                            //     if (password==1234567890) {break;}
                            //     cout<<"Incorrect password!"<<endl;
                            //     system("pause");
                                
                            // }
                            product_changer = 0;
                            while (product_changer!=5)

                            {

                                system("cls");
                                cout<<"1. Add Shirt"<<endl;
                                cout<<"2. Add Belt"<<endl;
                                cout<<"3. Add Chair"<<endl;
                                cout<<"4. Add Table"<<endl;
                                cout<<"5. Back"<<endl;
                                
                                cin>>product_changer;
                                system("cls");
                                switch (product_changer)
                                    {

                                        case 1:

                                            {
                                                int cost_of_shirt;
                                                string name_of_shirt;
                                                string descr_of_shirt;
                                                int size_of_shirt;
                                                string sex_of_shirt;
                                                string color_of_shirt; 
                                                string material_of_shirt;
                                                cout<<"Enter parametrs of shirt!"<<endl;
                                                cout<<"Enter cost: "; cin>>cost_of_shirt; cout<<endl;
                                                cout<<"Enter name: "; cin>>name_of_shirt; cout<<endl;
                                                cout<<"Enter description: "; cin>>descr_of_shirt; cout<<endl;
                                                cout<<"Enter size: "; cin>>size_of_shirt; cout<<endl;
                                                cout<<"Enter sex: "; cin>>sex_of_shirt; cout<<endl;
                                                cout<<"Enter color: "; cin>>color_of_shirt; cout<<endl;
                                                cout<<"Enter material: "; cin>>material_of_shirt; cout<<endl;
                                                Products* t = new Shirts(cost_of_shirt, name_of_shirt, descr_of_shirt, size_of_shirt, sex_of_shirt, color_of_shirt, material_of_shirt);
                                                break;
                                                delete(t);
                                            }

                                        case 2:

                                            {
                                                int cost_of_belt;
                                                string name_of_belt;
                                                string descr_of_belt;
                                                int size_of_belt;
                                                string sex_of_belt;
                                                string is_double;
                                                cout<<"Enter parametrs of belt!"<<endl;
                                                cout<<"Enter cost: "; cin>>cost_of_belt; cout<<endl;
                                                cout<<"Enter name: "; cin>>name_of_belt; cout<<endl;
                                                cout<<"Enter description: "; cin>>descr_of_belt; cout<<endl;
                                                cout<<"Enter size: "; cin>>size_of_belt; cout<<endl;
                                                cout<<"Enter sex: "; cin>>sex_of_belt; cout<<endl;
                                                cout<<"Is belt double: "; cin>>is_double; cout<<endl;
                                                Products* t = new Belt(cost_of_belt, name_of_belt, descr_of_belt, size_of_belt, sex_of_belt, is_double);
                                                break;
                                                delete(t);
                                            }

                                        case 3:

                                            {
                                                int cost_of_chair;
                                                string name_of_chair;
                                                string descr_of_chair;
                                                int size_of_chair;
                                                string material_of_chair;
                                                string color_of_chair; 
                                                string is_back;
                                                string is_soft;     
                                                cout<<"Enter parametrs of chair!"<<endl;                                          
                                                cout<<"Enter cost: "; cin>>cost_of_chair; cout<<endl;
                                                cout<<"Enter name: "; cin>>name_of_chair; cout<<endl;
                                                cout<<"Enter description: "; cin>>descr_of_chair; cout<<endl;
                                                cout<<"Enter size: "; cin>>size_of_chair; cout<<endl;
                                                cout<<"Enter material: "; cin>>material_of_chair; cout<<endl;
                                                cout<<"Enter color: "; cin>>color_of_chair; cout<<endl;
                                                cout<<"Is chair has a back: "; cin>>is_back; cout<<endl;
                                                cout<<"Is chair soft: "; cin>>is_soft; cout<<endl;
                                                Products* t = new Chair(cost_of_chair, name_of_chair, descr_of_chair, size_of_chair, material_of_chair, color_of_chair, is_back, is_soft);
                                                break;
                                                delete(t);
                                            }

                                        case 4:

                                            {
                                                int cost_of_table;
                                                string name_of_table;
                                                string descr_of_table;
                                                int size_of_table;
                                                string material_of_table;
                                                string color_of_table; 
                                                string is_mutable;
                                                cout<<"Enter parametrs of table!"<<endl;
                                                cout<<"Enter cost: "; cin>>cost_of_table; cout<<endl;
                                                cout<<"Enter name: "; cin>>name_of_table; cout<<endl;
                                                cout<<"Enter description: "; cin>>descr_of_table; cout<<endl;
                                                cout<<"Enter size: "; cin>>size_of_table; cout<<endl;
                                                cout<<"Enter material: "; cin>>material_of_table; cout<<endl;
                                                cout<<"Enter color: "; cin>>color_of_table; cout<<endl;
                                                cout<<"Is table mutable: "; cin>>is_mutable; cout<<endl;
                                                Products* t = new Table(cost_of_table, name_of_table, descr_of_table, size_of_table, material_of_table, color_of_table, is_mutable);
                                                break;
                                                delete(t);
                                            }

                                        default:
                                            break;

                                    }

                            }
                            BigMac(Products::count);
                            break;
                        }

                    case 2:
                        { 
                            system("cls");
                            cout<<"WELCOME TO THE SHOP"<<endl;
                            Products::read_count = 0;
                            fstream f;
                            f.open("C:\\vs_code_main\\best_internet_shop\\Stock.bin", ios::in | ios::binary);
                            while (f.read(reinterpret_cast<char*>(&read_type), sizeof(int))) 
                            {
                                switch (read_type)
                                {
                                
                                case 100:
                                    {
                                        cout<<Products::read_count<<") Shirt:"<<endl;
                                        cout<<endl;
                                        Products::arr[Products::read_count] = new Shirts();
                                        Products::arr[Products::read_count]->read(Products::read_count, f);
                                        cout<<endl;
                                        cout<<endl;
                                        break;
                                    }

                                case 200:
                                    {
                                        cout<<Products::read_count<<") Belt:"<<endl;
                                        cout<<endl;
                                        Products::arr[Products::read_count] = new Belt();
                                        Products::arr[Products::read_count]->read(Products::read_count, f);
                                        cout<<endl;
                                        cout<<endl;
                                        break;
                                    }

                                case 300:
                                    {
                                        cout<<Products::read_count<<") Chair:"<<endl;
                                        cout<<endl;
                                        Products::arr[Products::read_count] = new Chair();
                                        Products::arr[Products::read_count]->read(Products::read_count, f);
                                        cout<<endl;
                                        cout<<endl;
                                        break;
                                    }

                                case 400:
                                    {
                                        cout<<Products::read_count<<") Table:"<<endl;
                                        cout<<endl;
                                        Products::arr[Products::read_count] = new Table();
                                        Products::arr[Products::read_count]->read(Products::read_count, f);
                                        cout<<endl;
                                        cout<<endl;
                                        break;
                                    }
                                        
                                
                                }

                                Products::read_count++;
                            }
                            f.close();
                            Products::count = 0;
                            break;
                        } 
                    
                    case 3:
                        {  
                            int basket_changer = 0;                         
                            int total_cost = 0;
                            int thing_count;
                            int thing_in_basket_count;
                            
                            cout<<"1. Add thing to basket"<<endl;
                            cout<<"2. Open basket"<<endl;
                            cout<<"3. See total cost"<<endl;
                            cout<<"4. Remove thing from basket"<<endl;
                            cout<<"5. Buy"<<endl;
                            cout<<"6. Clear"<<endl;
                            cout<<"7. Back"<<endl;
                            Basket basket;
                            while (basket_changer!=7)
                                {
                                    cin>>basket_changer;
                                    switch (basket_changer)
                                        {
                                            case 1:
                                                {
                                                    basket.AddThings();
                                                    break;
                                                }

                                            case 2:
                                                {
                                                    basket.OpenBasket();
                                                    break;
                                                }

                                            case 3:
                                                {
                                                    basket.TotalCost();
                                                    break;
                                                }
                                            
                                            case 4:
                                                {
                                                    basket.RemoveThings();
                                                    break;
                                                }
                                            case 5:
                                                {
                                                    basket.Buy();
                                                    break;
                                                }

                                            case 6:
                                                {
                                                    system("cls");
                                                    cout<<"1. Add thing to basket"<<endl;
                                                    cout<<"2. Open basket"<<endl;
                                                    cout<<"3. See total cost"<<endl;
                                                    cout<<"4. Remove thing from basket"<<endl;
                                                    cout<<"5. Buy"<<endl;
                                                    cout<<"6. Clear"<<endl;
                                                    cout<<"7. Back"<<endl;
                                                    break;
                                                }
                                                
                                            default:
                                                break;
                                            
                                        }
                                }
                                

                        } 

                    case 4:
                        system("cls");

                    default:
                        break;

                }
        }
}
