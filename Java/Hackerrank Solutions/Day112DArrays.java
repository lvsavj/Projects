import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Day112DArrays {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int arr[][] = new int[6][6];
        int temp=0;
        int max=Integer.MIN_VALUE;
        for(int i=0; i < 6; i++){
            for(int j=0; j < 6; j++){
                arr[i][j] = in.nextInt();
            }
        }
        for (int a=0; a<6; a++) {
            for (int b=0; b<6; b++) {
                if(6-a>=3) {
                    if(6-b>=3) {
                        temp = arr[a][b] + arr[a][b+1] + arr[a][b+2] + arr[a+1][b+1] + arr[a+2][b] + arr[a+2][b+1] + arr[a+2][b+2];
                    }
                }
                if(temp>max) {
                    max=temp;
                }
            }
        }
        System.out.println(max);
    }
}
