import java.util.Scanner;

public class Proj1CPAR {

	public static void OnMult(int l, boolean line) {
		
		int i,j,k;
		double temp;
		long startTime, endTime;
		
		double a[] = new double[l*l];
		double b[] = new double[l*l];
		double c[] = new double[l*l];
		
		for(i=0; i<l*l; i++) {
			a[i] = (double)1.0;
			c[i] = (double)0.0;
		}

		for(i=0; i<l; i++)
			for(j=0; j<l; j++)
				b[i*l + j] = (double)(i+1);
				
				
		startTime = System.currentTimeMillis();
		
		if (line) {
			for(i=0; i<l; i++) {	
				for( k=0; k<l; k++) {
					for( j=0; j<l; j++) {	
						c[i*l+j] += a[i*l+k] * b[k*l+j];			
					}
				}
			}
		} else {
			for(i=0; i<l; i++) {	
				for( j=0; j<l; j++) {	
					for( k=0; k<l; k++)	{	
						c[i*l+j] += a[i*l+k] * b[k*l+j];
					}
				}
			}
		}
				
		endTime = System.currentTimeMillis();
		
		double elapsedTime = (double) (endTime - startTime) / 1000;
		System.out.println("Time: " + elapsedTime + "seconds");
		
		System.out.println("Result matrix: ");
		for(j=0; j<Math.min(10,l); j++) {
			System.out.print(c[j] + " ");
		}
		System.out.println();
	}

	public static void main(String args[]) {
		if (args.length >= 2) {
			OnMult(Integer.parseInt(args[1]), args[0].equals("2"));
			return;
		}
		
		Scanner reader = new Scanner(System.in); 
		
		int op = 1, size;
		do {
			System.out.println("");
			System.out.println("1. Multiplication");
			System.out.println("2. Line Multiplication");
			System.out.println("Selection?:");
			op = reader.nextInt();
			if (op == 0) break;
			System.out.println("Dimensions?:");
			size = reader.nextInt();
			
			switch (op){
			case 1: 
				OnMult(size, false);
				break;
			case 2:
				OnMult(size, true);
				break;
			}
			
		} while(op != 0);		
		
	}
}
