import java.io.*;
import java.util.*;
import java.awt.*;

public class One {
    public static void main(String[] args) throws Exception {
	Scanner input = new Scanner(new File("input"));
	input.useDelimiter(", ");

	int currDirection = 0;	// 0 North, 1 East, 2 South, 3 West

	HashSet<Point> visited = new HashSet<Point>();
	    
	// Only need to keep track of two dimension distances - use negative
	// numbers to represent going the opposite direction
	int n = 0;		// distance to travel north
	int e = 0;		// distance to travel east
	
	// Follow each instruction
	while (input.hasNext()) {
	    // Parse
	    String instruction = input.next();

	    char turn = instruction.charAt(0);
	    int amount = Integer.parseInt(instruction.substring(1,instruction.length()));
	    
	    // Update direction

	    if (turn == 'R') {
		currDirection++;
	    } else {
		currDirection--;
	    }

	    if (currDirection > 3) {
		currDirection = 0;
	    } else if (currDirection < 0) {
		currDirection = 3;
	    }

	    // Update distance travelled
	    for (int i = 0; i < amount; i++) {
		if (currDirection == 0) {
		    n++;
		} else if (currDirection == 1) {
		    e++;
		} else if (currDirection == 2) {
		    n--;
		} else if (currDirection == 3) {
		    e--;
		}

		Point currLoc = new Point(n, e);
		if (visited.contains(currLoc)) {
		    System.out.println(Math.abs(currLoc.x) + Math.abs(currLoc.y));
		}

		visited.add(currLoc);
	    
		// System.out.println (instruction);
		// System.out.println("Added " + amount + " to direction " + currDirection);
	    // System.out.println(Math.abs(n) + Math.abs(e));
	    }
	}

	System.out.println(Math.abs(n) + Math.abs(e));
    }
}
