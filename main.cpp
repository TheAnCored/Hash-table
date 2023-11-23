#include "hashtable.hpp"

int main(){

    unsigned int amount=0;
    char answ = 8;

    while(answ!='f' || answ != 'r' || answ != 'F' || answ != 'R'){
        std::cout<<" Do you wanna read from file or fill it our yourself?( read(r), fill(f))\n";
        std::cin >> answ;

        if(answ == 'f' || answ =='F'|| answ == 'r' || answ =='R'){ break; }
        else{
//          answ = 8;
            std::cout<<" Input again(read(r) or fill(f)): \n"; std::cin>>answ; std::cout<<std::endl;
        }
    }

    HashTable table = HashTable();

    if(answ == 'r' || answ == 'R'){

        std::cout<< " Reading from file 'data.txt'...\n";
        std::ifstream file;
        file.open("data.txt");

        if(file.is_open()==false){ std::cout<<" File isn't found! Try to fill yourself!\n";}
        else{
            reading_from_file(file, table);
            file.close();
        }
    }
    else{
        std::cout<<" Input the amount elements of the table: ";
        std::cin >> amount; std::cout<<std::endl;
        table.reconstruct(amount);
    }
    


    while(answ != '\n'){
        std::cout<<" What do you want to do ( add item(a), delete item(d), search(s), edit(e), output(o), exit(n)):\n";
        std::cin >> answ;

        std::string str;

        switch(answ){
            case 'a':
                std::cout<<" Input string to add: "; std::cin>> str; std::cout << std::endl;
                table.add(str);

                break;

            case 'd':
                std::cout << " Input string to delete: \n";
                std::cin >> str; std::cout<<str<<std::endl;

                table.pop(str);

                break;

            case 's':
                std::cout << " Input string to search: \n";
                std::cin >> str; std::cout<<std::endl;

                if(table.search(str)==true){ std::cout<<" Yes "<<std::endl; }
                else{ std::cout<<" No "<<std::endl; }

                break;

            case 'e':
                std::cout<<" Input string to edit them: \n";
                std::cin>> str; 

                if(table.search(str)==true){ 

                    table.pop(str);
                    std::cout<<" Rewrite string: "; 
                    std::cin>>str;std::cout<<std::endl; 
                    table.add(str);

                    table.output();
                }
                else{ std::cout<<" That string wasn't found in the table! \n\n"<<std::endl; }

                break;

            case 'o':
                table.output();

                break;

            case 'n':
                answ = '\n';
                std::cout<< "\n\n GOOD BYE!!! \n\n";
                table.delete_table();

                break;


            default:
                std::cout<< " Input again (a, d, s, e, o, n): \n";
                std::cin >> answ; std::cout<<std::endl;

                break;
        }
    }

    return 0;
}
