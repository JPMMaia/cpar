import java.util.Scanner;

public class prog_java {

	public static double OnMult(int l, boolean line) {
		
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
				
				
		startTime = System.nanoTime();
		
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
				
		endTime = System.nanoTime();
		
		return (double) (endTime - startTime) / 1e9;
		//System.out.println("Time: " + elapsedTime + "seconds");
		
		/*System.out.println("Result matrix: ");
		for(j=0; j<Math.min(10,l); j++) {
			System.out.print(c[j] + " ");
		}
		System.out.println();*/
	}

	public static void main(String args[]) {
		if (args.length >= 2) {
			double time = OnMult(Integer.parseInt(args[1]), args[0].equals("1"));
			
			System.out.println(time);
			
		} else {
			Scanner reader = new Scanner(System.in); 
			
			while(reader.hasNext()) {
				boolean line_mult = (reader.nextInt() != 0);
				int size = reader.nextInt();
				int n_omp = reader.nextInt();
				
				double time = OnMult(size, line_mult);
		
				System.out.println((line_mult?1:0) + " " + size + " " + time);
			}
		}	
	}
}
