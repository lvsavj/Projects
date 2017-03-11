import java.util.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int q[] = new int[in.nextInt()];
		for(int z=0;z<q.length;z++){
            q[z] = in.nextInt();
        }
		System.out.println(java.util.Arrays.stream(q).sum());
	}
}