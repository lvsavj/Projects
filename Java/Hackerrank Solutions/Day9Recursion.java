import java.io.*;
import java.util.*;

public class Day9Recursion {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        
        //Read integer
        int n = sc.nextInt();
        //Factorial f=new Factorial(n);
        int printFact=Factorial(n);
        System.out.println(printFact);
    
    }
    
    private static int Factorial(int n) {
        if(n<=1)
            return 1;
        else
            return n*Factorial(n-1);
        
    }
}