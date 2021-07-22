int foo() 
{ 
    volatile int abc = 10;
    abc++;
    return abc;
}
