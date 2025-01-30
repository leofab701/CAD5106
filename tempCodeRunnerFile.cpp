///////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
    int looper=1000000, addr, flag, shift;

    cout << "Please, enter 0 for Direct mapped, 1 for set associative, 2 for fully associative: " << endl;
    cin >> cash_type;
    cout << "Please, enter the size of the block as a Power of 2 between 4 and 128 byte  :" << endl;
    cin >> block_size;
    cout << "Please, enter cache size: 1KB – 64KB; in steps that are power of 2: " << endl;
    cin >> cash_size;
    
    

    int cash[3][100000];
    int block_counter=0;
    int hit_counter=0;
    int index_addr=0, tag_addr=0;
    
    ///////////////////////////////////////////////////////////////////
    if ( cash_type==0)   //Direct_mapped **************
    {
        number_of_blocks= (cash_size*1024)/block_size;
        
        ////////////////////
        for (int i=0; i < 2; i++)   // setting all the cash with -1
            for (int j=0; j < number_of_blocks; j++)
                cash[i][j]=-1;
        //////////////////
        
        for(int i=0; i <looper ;i++)
        {
            addr = memGen1();
            shift= log2(block_size);
            index_addr= (addr >> shift)% number_of_blocks;
            shift= log2(number_of_blocks+block_size);
            tag_addr= addr >>shift;    // shifted the amount the offset and the index sizes
            flag = cacheSim(addr, cash, 0,block_counter, index_addr, tag_addr);
            index_addr=0;
            tag_addr=0;
            cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[flag] <<")\n";
            if (msg[flag]=="Hit")
            {
                hit_counter++;
            }
        }
    cout << "Hits  " << hit_counter<<endl << "Compulsry:  " << compulsry_misses <<endl<< "Capcity:  " << capcity_misses <<endl<< "Conflict:  " << conflict_misses <<  endl;

    }
    ///////////////////////////////////////////////////////////////////
    else if (cash_type==2)  //  Fully associative**************
    {
        int replacment_type;
        number_of_blocks= (cash_size*1024)/block_size;
        
        cout << "please, enter the type of replacment for the Fully Associative: LRU->0 , LFU->1, FIFO->2, RANDOM->3  :- " << endl;
        cin >> replacment_type;
        
        
        for (int i=0; i < 2; i++)   // setting all the cash with -1
            for (int j=0; j < number_of_blocks; j++)
                cash[i][j]=-10;
        
        for(int i=0; i <looper ;i++)
        {
            addr = memGen4();
            flag = cacheSim(addr, cash, replacment_type, block_counter, index_addr, tag_addr);
           // cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[flag] <<")\n";
            
            if (msg[flag]=="Hit")
            {
                hit_counter++;
            }
            block_counter++;

        }
        
        cout << "Hits  " << hit_counter<<endl << "Compulsry:  " << compulsry_misses <<endl<< "Capcity:  " << capcity_misses <<endl<< "Conflict:  " << conflict_misses <<  endl;
        
    } // end of fully associative main
    else if (cash_type==1) // set associative
    {
        int number_of_ways;
        cout << "please, enter the number of ways for the set associative cash: 2,4,8,16" << endl;
        cin >> number_of_ways;
        number_of_blocks= (cash_size*1024)/(block_size*number_of_ways);
        
        for (int i=0; i < 3; i++)   // setting all the cash with -1
            for (int j=0; j < 100000; j++)
                cash[i][j]=-1;
        
        for(int i=0; i <looper ;i++)
        {
            addr = memGen5();
            shift= log2(block_size);
            index_addr= (addr >> shift)% (number_of_blocks);
            shift= log2(number_of_blocks+block_size);
            tag_addr= addr >>shift;
            flag = cacheSim(addr, cash, number_of_ways, block_counter, index_addr, tag_addr);
            // cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[flag] <<")\n";
            index_addr=0;
            tag_addr=0;
            if (msg[flag]=="Hit")
            {
                hit_counter++;
            }
            block_counter++;
        }
        
        cout << "Hits  " << hit_counter<<endl << "Compulsry:  " << compulsry_misses <<endl<< "Capcity:  " << capcity_misses <<endl<< "Conflict:  " << conflict_misses <<  endl;
    }
  
}


