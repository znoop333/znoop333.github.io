// sudokusolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <strstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <fstream>
#include <exception>
#include <queue>

using namespace std;

// zero-based indices into a 9x9x10 array: 
// entry(i,j,0) is 0    if the value is currently unknown
//                 1-9  if the value is known
// entry(i,j,1) is 1    if 1 is a permissible value for (i,j)
//                 0    if 1 can't be the value in (i,j)
// entry(i,j,2) is 1    if 2 is a permissible value for (i,j)
//                 0    if 2 can't be the value in (i,j)
// etc. through entry(i,j,9)
#define SUB2IND(i1,j1,k1) (i1 + j1*9 + k1*9*9)
#define SUB2IND2(i1,j1) (i1 + j1*9)
typedef vector<int> vInt;
typedef pair<int,int> iiPair;
typedef priority_queue<iiPair> pqInt;

// helper class: given coordinates into the grid, which other coordinates are inside the same box?
class NeighborhoodBox 
{
public:
	// coordinates of neighborhood are located at (N1(0), N2(0)), (N1(1), N2(1)), ... (N1(8), N2(8))
	vInt N1, N2;
	NeighborhoodBox() : N1(9,0), N2(9,0) {}
	~NeighborhoodBox() {}

	//int boxIdx; 
};

// there are 9 boxes with indices 0 to 8.
typedef vector<NeighborhoodBox> vNeighborhood;

class NeighborhoodHelper
{
public:
	vNeighborhood neighborhoods;
	NeighborhoodHelper()
	{
		neighborhoods = vNeighborhood(9);

		// each neighborhood has similar coordinates with an offset wrt. the upper left hand box
		vInt offsets1 = vInt(9,0);
		vInt offsets2 = vInt(9,0);
		offsets1[0]=0;
		offsets2[0]=0;

		offsets1[1]=1;
		offsets2[1]=0;

		offsets1[2]=2;
		offsets2[2]=0;

		offsets1[3]=0;
		offsets2[3]=1;

		offsets1[4]=1;
		offsets2[4]=1;

		offsets1[5]=2;
		offsets2[5]=1;

		offsets1[6]=0;
		offsets2[6]=2;

		offsets1[7]=1;
		offsets2[7]=2;

		offsets1[8]=2;
		offsets2[8]=2;

		for(int ii=0; ii<3; ii++)
		{
			for(int jj=0; jj<3; jj++)
			{
				int offsetUpperLeft1 = ii*3;
				int offsetUpperLeft2 = jj*3;
				int neighIdx = ii + jj*3;
				for(int kk=0; kk<9; kk++)
				{
					neighborhoods[neighIdx].N1[kk] = offsetUpperLeft1 + offsets1[kk];
					neighborhoods[neighIdx].N2[kk] = offsetUpperLeft2 + offsets2[kk];
				}
			}
		}
	}

	~NeighborhoodHelper() {}

	// given coordinates somewhere in the grid, determine the index of the box it's in.
	static int Coordinates2Box(int ii, int jj)
	{
		if(ii>=0 && ii<=2)
		{
			if(jj>=0 && jj<=2)
				return 0;
			else if(jj>=3 && jj<=5)
				return 3;
			else if(jj>=6 && jj<=8)
				return 6;
			else
				throw out_of_range("jj");
		}
		else if(ii>=3 && ii<=5)
		{
			if(jj>=0 && jj<=2)
				return 1;
			else if(jj>=3 && jj<=5)
				return 4;
			else if(jj>=6 && jj<=8)
				return 7;
			else
				throw out_of_range("jj");
		}
		else if(ii>=6 && ii<=8)
		{
			if(jj>=0 && jj<=2)
				return 2;
			else if(jj>=3 && jj<=5)
				return 5;
			else if(jj>=6 && jj<=8)
				return 8;
			else
				throw out_of_range("jj");
		}
		else
				throw out_of_range("ii");

		// should be unreachable
		return -1;
	}

	// given a box, return the coordinates of the neighbors by assigning them to the arguments
	bool Box2Coordinates(int boxIdx, vInt &n1, vInt &n2)
	{
		if(boxIdx<0 || boxIdx>8)
			return 0;
		n1 = neighborhoods[boxIdx].N1;
		n2 = neighborhoods[boxIdx].N2;
		return 1;
	}

};




class SudokuPuzzle 
{
public:
	int id;
	vInt grid;
	vInt solutionsCounter; // count of how many solutions are possible in each square
	pqInt pqMostConstrained; // priority_queue containing <-number of solutions, array index of square> for every unsolved square
	NeighborhoodHelper nh;

	SudokuPuzzle()
	{
		id = -1;
		grid = vInt(9*9*10, 0);
		solutionsCounter = vInt(9*9, 9);
		Reset();
	}

	~SudokuPuzzle() {}
	
	// the default state is that no digits are known and all values are permitted in every square
	void Reset()
	{
		for(int i=0; i<9; i++)
			for(int j=0; j<9; j++)
			{
				grid[SUB2IND(i,j,0)] = 0;
				for(int n=1; n<=9; n++)
				{
					grid[SUB2IND(i,j,n)] = 1;
				}
				solutionsCounter[SUB2IND2(i,j)] = 9;
			}
	}

	// the puzzle is solved when every space has an assigned, known value
	bool IsSolved()
	{
		for(int i=0; i<9; i++)
			for(int j=0; j<9; j++)
			{
				if (grid[SUB2IND(i,j,0)] == 0)
					return false;
			}

		return true;
	}

	string ToString() 
	{
		stringstream os;
		os << " _________________________" << endl;
		for(int i=0; i<9; i++)
		{
			os << "| ";
			for(int j=0; j<9; j++)
			{
				os << grid[SUB2IND(i,j,0)] << " ";

				if(j==2 || j==5)
					os << " | ";
			}
			os << "|" << endl;

			if(i==2 || i==5)
				os << "--------------------------" << endl;
		}
		os << " -------------------------" << endl;

		return os.str();
	}

	bool Parse(string& s)
	{
		int i=0, j=0;

		for(int k=0; k<s.length(); k++)
		{
			if(!isdigit(s[k]))
				continue;
			int n = s[k] - '0';

			grid[ SUB2IND(i,j,0) ] = n;
			
			// logical array: 0s for everything but entry n
			if(n > 0)
			{
				for(int n2=1; n2<=9; n2++)
					grid[ SUB2IND(i,j,n2) ] = 0;

				grid[ SUB2IND(i,j,n) ] = 1;
			}

			j++;
			if(j>8)
			{
				j=0;
				i++;
			}
		}


		return 1;
	}

	// if a non-zero digit is known to occur somewhere, go along the corresponding row, column, and box
	// and mark it to be impossible in those other locations
	//
	// returns the number of changes made to the grid. may be zero!
	int PropagateDigits()
	{
		int ChangesMade = 0;

		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				stringstream os;
				int ChangesMadeThisSquare = 0;

				int n1=grid[SUB2IND(i,j,0)];
				if (n1 == 0)
					continue;

				// row
				os << "Updates for (" << i << ", " << j << ")[" << n1 << "]: ";
				for(int j1=0; j1<9; j1++)
				{
					if(j1==j)
						continue; // don't overwrite the current square

					if( grid[SUB2IND(i,j1,n1)] != 0 )
					{
						ChangesMade++;
						ChangesMadeThisSquare++;
						grid[SUB2IND(i,j1,n1)] = 0;
						os << "(" << i << ", " << j1 << "), ";
					}
				}

				// column
				for(int i1=0; i1<9; i1++)
				{
					if(i1==i)
						continue; // don't overwrite the current square

					if( grid[SUB2IND(i1,j,n1)] != 0 )
					{
						ChangesMade++;
						ChangesMadeThisSquare++;
						grid[SUB2IND(i1,j,n1)] = 0;
						os << "(" << i1 << ", " << j << "), ";
					}
				}

				// box
				vInt d1, d2;
				int boxIdx = NeighborhoodHelper::Coordinates2Box(i,j);
				nh.Box2Coordinates(boxIdx, d1, d2);

				for(int d=0; d<=8; d++)
				{
					if(i==d1[d] && j==d2[d])
						continue; // don't overwrite the current square

					if( grid[SUB2IND(d1[d],d2[d],n1)] != 0 )
					{
						ChangesMade++;
						ChangesMadeThisSquare++;
						grid[SUB2IND(d1[d],d2[d],n1)] = 0;
						os << "(" << d1[d] << ", " << d2[d] << "), ";
					}
				}

				//if(ChangesMadeThisSquare>0)
				//	cout << os.str() << endl;
			}
		}

		return ChangesMade;
	}

	// for each square with only one possible solution, choose that solution
	// returns the number of squares updated. also keep count of how many solutions are possible in each square.
	int DeductionPhase()
	{
		int squaresFound=0;

		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				if (grid[SUB2IND(i,j,0)] > 0)
					continue; // this square is already solved

				int numSoln = 0;
				int possSoln = -1;
				for(int n=1; n<=9; n++)
				{
					if (grid[SUB2IND(i,j,n)] == 1)
					{
						numSoln++;
						possSoln = n;
					}
				}

				if(numSoln==0)
				{
					stringstream os;
					os << "Impossible state at (" << i << ", " << j << ") -- no solutions possible!" << endl;
					
					os << "Current value: " << grid[SUB2IND(i,j,0)] << " with logical array: ";
					
					for(int n2=1; n2<=9; n2++)
					{
						os << grid[SUB2IND(i,j,n2)];
					}

					//cout << os.str();

					throw logic_error(os.str());
				}
				else if(numSoln==1)
				{
					squaresFound++;
					grid[SUB2IND(i,j,0)] = possSoln;
				}
				//else: multiple solutions! this case is handled by a different algorithm



			}
		}
		
		return squaresFound;
	}

	// since every row must have each digit 1-9 in it somewhere, we may be able to infer the location
	// of a particular missing digit in the row (e.g., 4) by determining that only one of the unknown
	// squares in the row will allow that digit to occur (e.g., at (2,1) but not (3,1)). 
	//
	// repeat this argument for columns and boxes, and it forces the existance of more digits.
	int PositiveConstraintEnforcement()
	{
		int squaresFound=0;
		vInt digitsFound = vInt(10,0); // 0th digit is unused

		// rows
		for(int i=0; i<9; i++)
		{
			digitsFound = vInt(10,0);
			for(int j=0; j<9; j++)
			{
				if (grid[SUB2IND(i,j,0)] > 0)
					digitsFound[ grid[SUB2IND(i,j,0)] ] ++;
			}

			// now we know which digits haven't been used in the row yet.
			// determine if there is only one square in the row which will accept a given digit
			for(int d=1; d<=9; d++)
			{
				if (digitsFound[d] > 0)
					continue;

				int possSolns=0;
				int lastSoln=-1;

				for(int j2=0; j2<9; j2++)
				{
					if (grid[SUB2IND(i,j2,d)] == 1)
					{
						possSolns++;
						lastSoln = j2;
					}
				}

				if(possSolns == 0)
				{
					stringstream os;
					os << "Impossible state in row (" << i << ") -- no solutions possible for " << d << endl; 
					// cout << os.str();

					throw logic_error(os.str());
				}
				else if (possSolns == 1)
				{
					// great! we found the right place for d
					for(int n2=1; n2<=9; n2++)
					{
						grid[SUB2IND(i,lastSoln,n2)] = 0;
					}
					grid[SUB2IND(i,lastSoln,0)] = d;
					grid[SUB2IND(i,lastSoln,d)] = 1;
					squaresFound++;
				}
				// else: multiple solutions, much harder. solved elsewhere.
			}
		} // end for rows




		// columns
		for(int j=0; j<9; j++)
		{
			digitsFound = vInt(10,0);
			for(int i=0; i<9; i++)
			{
				if (grid[SUB2IND(i,j,0)] > 0)
					digitsFound[ grid[SUB2IND(i,j,0)] ] ++;
			}

			// now we know which digits haven't been used in the column yet.
			// determine if there is only one square in the column which will accept a given digit
			for(int d=1; d<=9; d++)
			{
				if (digitsFound[d] > 0)
					continue;

				int possSolns=0;
				int lastSoln=-1;

				for(int i2=0; i2<9; i2++)
				{
					if (grid[SUB2IND(i2,j,d)] == 1)
					{
						possSolns++;
						lastSoln = i2;
					}
				}

				if(possSolns == 0)
				{
					stringstream os;
					os << "Impossible state in column (" << j << ") -- no solutions possible for " << d;
					//cout << os.str();

					throw logic_error(os.str());
				}
				else if (possSolns == 1)
				{
					// great! we found the right place for d
					for(int n2=1; n2<=9; n2++)
					{
						grid[SUB2IND(lastSoln,j,n2)] = 0;
					}
					grid[SUB2IND(lastSoln,j,0)] = d;
					grid[SUB2IND(lastSoln,j,d)] = 1;
					squaresFound++;
				}
				// else: multiple solutions, much harder. solved elsewhere.
			}
		} // end for columns


		// boxes
		for(int boxIdx=0; boxIdx<9; boxIdx++)
		{
			digitsFound = vInt(10,0);

			vInt d1, d2;
			nh.Box2Coordinates(boxIdx, d1, d2);

			for(int b=0; b<=8; b++)
			{
				if (grid[SUB2IND(d1[b],d2[b],0)] > 0)
					digitsFound[ grid[SUB2IND(d1[b],d2[b],0)] ] ++;
			}

			// now we know which digits haven't been used in the box yet.
			// determine if there is only one square in the box which will accept a given digit
			for(int d=1; d<=9; d++)
			{
				if (digitsFound[d] > 0)
					continue;

				int possSolns=0;
				int lastSoln1=-1;
				int lastSoln2=-1;

				for(int b2=0; b2<=8; b2++)
				{
					if (grid[SUB2IND(d1[b2],d2[b2],d)] == 1)
					{
						possSolns++;
						lastSoln1 = d1[b2];
						lastSoln2 = d2[b2];
					}
				}

				if(possSolns == 0)
				{
					stringstream os;
					os << "Impossible state in box (" << boxIdx << ") -- no solutions possible for " << d;
					//cout << os.str();

					throw logic_error(os.str());
				}
				else if (possSolns == 1)
				{
					// great! we found the right place for d
					for(int n2=1; n2<=9; n2++)
					{
						grid[SUB2IND(lastSoln1,lastSoln2,n2)] = 0;
					}
					grid[SUB2IND(lastSoln1,lastSoln2,0)] = d;
					grid[SUB2IND(lastSoln1,lastSoln2,d)] = 1;
				}
				// else: multiple solutions, much harder. solved elsewhere.
			}
		} // end for boxes


		return squaresFound;
	}

	
	// using only Propagation, Deduction, and PCE, iterate on the current puzzle until no changes occur or the maximum number of iterations is reached.
	// returns the number of changes which occurred since starting (may be zero).
	// maxIter=0 will iterate until no changes occur.
	int IterateUntilConvergence(int maxIter=0)
	{
		int totalChanges=0, lastTotalChanges=-1;
		int iterationCounter=0;
		int unsolvedCount=0;

		// non-negative max iter
		maxIter = (maxIter<0 ? 0 : maxIter);

		do
		{
			iterationCounter++;
			lastTotalChanges = totalChanges;
			int nc = PropagateDigits();
			int np = DeductionPhase();
			int pce = PositiveConstraintEnforcement();
			totalChanges += nc + np + pce;
			unsolvedCount = UpdateSolutionCount();
		} while (unsolvedCount > 0 && totalChanges != lastTotalChanges && (maxIter && iterationCounter < maxIter));

		return totalChanges;
	}
	
	// for every non-solved square, count the number of solutions remaining and store it internally.
	// also rebuild the priority queue of indices containing the fewest number of solutions
	int UpdateSolutionCount()
	{
		int numUnsolved=0;

		// empty out the priority_queue
		while(!pqMostConstrained.empty())
			pqMostConstrained.pop();

		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				if (grid[SUB2IND(i,j,0)] > 0)
					solutionsCounter[SUB2IND2(i,j)] = 1; 
					// do not add this element to the queue because it's already solved!
				else
				{
					numUnsolved++;
					int possSolns=0;
					for(int d=1; d<=9; d++)
					{
						if (grid[SUB2IND(i,j,d)] == 1)
							possSolns++;
					}
					solutionsCounter[SUB2IND2(i,j)] = possSolns;

					// must negate the number of solutions because priority_queue will return the maximum element
					// pair<int,int> will sort by .first (number of solutions) and then by .second (array index)
					pqMostConstrained.push(make_pair(-possSolns, SUB2IND2(i,j)));
				}
			}
		}

		return numUnsolved;
	}


	;
};

typedef vector<SudokuPuzzle> vSudokuPuzzle;

// hypothesis testing: suppose there are no squares which can be solved using Propagation, Deduction, or PCE.
// we will find the square with the fewest possible solutions (min 2, max 9, obviously)
// and recursively test each of those solutions until either:
//       1) the puzzle is unambiguously solved, or
//       2) an unavoidable contradiction is derived (via exceptions thrown), or
//		 3) recursive testing goes too deep (stack overflow) to get 1) or 2).
//
// this is essentially equivalent to depth first search on a tree with up to 9 branches at each node,
// corresponding to the choices of digits in each square. we're hoping that 3) doesn't occur often
// but it could if there is no unique solution. 
//
// returns a vector containing: zero SudokuPuzzles (no solutions exist),
// one SudokuPuzzle (a unique solution exists),
// or several partially solved SudokuPuzzles (the initial problem iterates until multiple solutions are possible and cannot be resolved due to ambiguity in the original problem)
vSudokuPuzzle HypothesisTesting(SudokuPuzzle& initSP, int maxDepth=20)
{
	vSudokuPuzzle vsp;

	if(maxDepth<=0)
		return vsp; // refuse to recurse further

	try 
	{
		initSP.IterateUntilConvergence();
	}
	catch (logic_error& lce)
	{
		// there's no way to solve this puzzle. 
		return vsp; // refuse to recurse further
	}

	if(initSP.IsSolved())
	{
		vsp.push_back(initSP);
		return vsp; // refuse to recurse further because this puzzle is already solved
	}

	// start testing possible hypotheses
	// take the most constrained square and create a new SudokuPuzzle for each of its possible solutions
	int nSolns = - initSP.pqMostConstrained.top().first;
	int idx = initSP.pqMostConstrained.top().second;
	initSP.pqMostConstrained.pop();

	int idx1 = idx % 9;
	int idx2 = idx / 9;

	for(int d=1; d<=9; d++)
	{
		if(initSP.grid[SUB2IND(idx1,idx2,d)] > 0)
			continue;

		SudokuPuzzle sp1 = initSP;

		// mark the new solution for this square
		for(int d2=1; d2<=9; d2++)
		{
			sp1.grid[SUB2IND(idx1,idx2,d)] = 0;
		}
		sp1.grid[SUB2IND(idx1,idx2,0)] = d;
		sp1.grid[SUB2IND(idx1,idx2,d)] = 1;

		// now try to solve it. 
		int solnFound = 0;
		try 
		{
			sp1.IterateUntilConvergence();
			solnFound = sp1.IsSolved();
		}
		catch (logic_error& lce)
		{
			solnFound = -1;
		}

		if(solnFound == -1)
		{
			// somehow this choice lead to a contradiction, so at least we can definitively say that it won't work
			continue;
		}
		else if(solnFound == 1)
		{
			// we actually solved it!
			vsp.push_back(sp1);
		}
		else
		{
			// indeterminant -- there are still unknown squares. try to recursively solve them 
			// under the assumption that the current choices are valid
			vSudokuPuzzle vsp2 = HypothesisTesting(sp1, maxDepth-1);
			vsp.insert(vsp.end(), vsp2.begin(), vsp2.end()); // append new solutions, if any
		}


	}





	return vsp; 
}

SudokuPuzzle ReadPuzzle(fstream& fs)
{
	SudokuPuzzle sp;
	string s, s2;
	int id;

	// read the first line: Grid XX
	fs >> s;
	fs >> id;

	getline(fs,s);
	s2.append(s);
	for(int i=1; i<=9; i++)
	{
		getline(fs,s);
		if(fs.bad() || fs.eof())
			break;
		s2.append(s);
	}

	sp.Parse(s2);
	sp.id = id;

	return sp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	fstream fs("sudoku.txt");

	while(fs.good())
	{
		SudokuPuzzle sp = ReadPuzzle(fs);

		cout << "Parsed to:\n" << sp.ToString();

		sp.IterateUntilConvergence(25);
		cout << sp.ToString();

		if (sp.IsSolved())
			cout << "Puzzle " << sp.id << " was solved!" << endl;
		else
		{
			cout << "Puzzle " << sp.id << " was not solved!" << endl;
			cout << "Recursively searching for more solutions..." << endl;
			vSudokuPuzzle vsp = HypothesisTesting(sp, 10);
			if(vsp.size() == 0)
			{
				cout << "No solutions found!" << endl;
				continue;
			}
			else if(vsp.size() == 1)
			{
				cout << "Exact solution found!" << endl;
				cout << vsp[0].ToString();
				continue;
			}

			cout << "Incomplete solutions found?!" << endl;
			for(int i=0; i<vsp.size(); i++)
			{
				cout << vsp[i].ToString();
			}
		}
	}

	return 0;
}

