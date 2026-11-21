
#include <iostream>
#include <ctime>
#include <limits>
#include <cstring>
#include <stdlib.h>
#include "../headers/block.h"


void fill_transaction(transaction *transaction_core){
    


    // record my ip add
    int status = system("hostname -I | awk '{print $1}' > my_ip.txt");
    if (status != 0){
        fprintf(stderr,"failed to curl the command");
        exit(0);
    }

    FILE * ip = fopen("my_ip.txt","r");
    if(ip == NULL){
        fprintf(stderr,"error opeing the file");
        exit(0);
    }

    if(fgets(transaction_core->sender,
        sizeof(transaction_core->sender),ip)!= NULL){
           // printf("Read IP from file: %s\n", transaction_core->sender);
           printf("ip recorded \n");
        }
    //eliminate the \n 
    transaction_core->sender[strcspn(transaction_core->sender, "\n")] = '\0';
    fclose(ip);
    // ip stored in sender






    std::cout<< "destination ip addr: ";
    std::cin >> transaction_core->destination;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "data: ";
    std::getline(std::cin, transaction_core->data);
    std::cout<<"[] The  transaction saved | no errors detected "<<'\n';
    //hashing data using sha256 with bash. so lazy to use another method
    FILE *temp = fopen("hash_temp.txt","w+");
    if(temp == NULL){
        fprintf(stderr,"error opening the file");
        return;
    }
    for (int i=0;i<256;i++){
        if(transaction_core->data[i] == '\0') break;
        fprintf(temp,"%c",transaction_core->data[i]);
    }
    fclose(temp);
    status = system("sha256sum hash_temp.txt | awk '{print $1}' > hash.txt && mv hash.txt hash_temp.txt");

    if ((temp=fopen("hash_temp.txt","r")) == NULL){
        perror("error opening the hashed file");
        return;
    }

    fgets(transaction_core->hash,sizeof(transaction_core->hash),temp);
    //transaction_core->hash[strcspn(transaction_core->hash, "\n")] = '\0';
    fclose(temp);
    transaction_core->timestamp = time(NULL);
    


   
    
    
}

void transaction_info(transaction *transaction_core){
      if(transaction_core == NULL)
      {
        fprintf(stderr,"trying to show transaction while it is empty?\n fill it first\n\n");
        return;
      }
      std::cout << transaction_core->data <<"\n";
            std::cout << "sender: " <<transaction_core->sender<<"\n";
            std::cout << "destination: "<<transaction_core->destination<<"\n";
            std::cout << "timestamp: "<<ctime(&transaction_core->timestamp)<<"\n";
            std::cout << "Hash: "<<transaction_core->hash<<"\n";
};

int main(void)
{
    transaction transaction_core = {};
    int input;
    while(true){
        std::cout <<"------------------------------------------------\n";
        std::cout<< "to start a transaction input : 1"<<"\n";
        //std::cout<< "to view blocks history input : 2"<<"\n";
        std::cout<< "print the transaction info. If not empty : 3"<<"\n";
        std::cout<< "annoyed already ? you can exit with : 0"<<"\n";
        std::cout << " >>>> ";
        std::cin >> input;

        

        switch(input){
            case 0:  exit(0);
            case 1:  fill_transaction(&transaction_core); break;
            case 3:  transaction_info(&transaction_core); break;
            
            default: std::cout << " not a valid option try again"; break;


        }
           

           
        
        
    }
 








    return 0;
}
