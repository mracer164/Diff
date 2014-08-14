#include <iostream>
#include <fstream>
using namespace std;
//structure of list element
struct diff_location
{
	int first_char;
	int second_char;
	int line_number;
	//pointer to next element
	diff_location *next;
	diff_location();
};
//constructor
diff_location::diff_location()
{
	next = 0;
}
//structure of a list
struct list
{
	//pointer to first element
	diff_location *first;
	void add_location(int first_char, int second_char, int line_number);
	void display_list();
	void output();
	list();
};

list::list()
{
	first = 0;
}
//method adding element to the list
void list::add_location(int first_char, int second_char, int line_number)
{
	diff_location *new_loc = new diff_location;
	new_loc->first_char = first_char;
	new_loc->second_char = second_char;
	new_loc->line_number = line_number;

	if(first==0)
	{
		first = new_loc;
	}
	else
	{
		diff_location *temp = first;
		while (temp->next)
        {
            temp = temp->next;
		}
		temp->next = new_loc;  
		new_loc->next = 0;   
	}
}
// method displaying all elements of a list
void list::display_list()
{
	diff_location *temp = first;
	if (first==0)
	{
		cout << "No differences were found." << endl;
	}
	int loc_numb = 1;
	while(temp!=0)
	{
		cout << loc_numb << ": Line: " << temp->line_number << " Beggining character: " << temp->first_char << " Ending character: " << temp->second_char << endl;
		temp=temp->next;
		loc_numb++;
	}
}
//method taking input of the user and editing file according to list data
void list::output()
{
	ifstream read_file("text.txt");
	ifstream read_file1("text1.txt");
	ofstream output_file("output.txt");
	int choice, i = 0, char_count = 0,line_count = 0;
	char chr,chr1;
	if (first!=0)
	{
	cout << "Which difference do you want to exchange?: " << endl;
	cin >> choice;
	diff_location *temp = first;
	while(i != choice-1)
	{
		temp=temp->next;
		i++;
	}
	cout << "Line: " << temp->line_number << " Beggining character: " << temp->first_char << " Ending character: " << temp->second_char << endl;
	while(read_file.good()||read_file1.good())
	{
		if((line_count==temp->line_number)&&(char_count==temp->first_char))
		{
			if(temp->first_char==temp->second_char)
			{
				output_file << chr1;
				chr = read_file.get();
				chr1 = read_file1.get();
				char_count++;
				
			}
			while((char_count!=((temp->second_char)+1))||(char_count==temp->first_char))
			{
				output_file << chr;
				chr = read_file.get();
				chr1 = read_file1.get();
				char_count++;
			}
			output_file << chr1;
			
		}
		else
		{
			chr = read_file.get();
			chr1 = read_file1.get();
			char_count++;
			if((line_count==temp->line_number)&&(char_count==temp->first_char))
				continue;
			if(chr=='\n')
			{
				line_count++;
				char_count=0;
			}
			output_file << chr1;
		}
		
	}
	output_file.close();
	}
	

	
}
//main function
int main ()
{
	cout << "Diff by Mateusz Derlecki. Gliwice 28.06.2014" << endl;
	list *loc_base = new list;
	char chr,chr1; 
	int char_count = 0, line_count = 0, f_char = 0, s_char = 0, diff_count = 0;
	ifstream read_file("text.txt");
	ifstream read_file1("text1.txt");
	//loop going through text files and seaching for differences
	while(read_file.good()||read_file1.good())
	{
		chr = read_file.get();
		chr1 = read_file1.get();
		if(chr == chr1)
		{
			char_count++;
			if(chr == '\n')
			{
				line_count++;
				char_count=0;
			}
			continue;
		}
		else
		{
			diff_count++;
			char_count++;
			f_char = char_count;
			chr = read_file.get();
			chr1 = read_file1.get();
			while(chr!=chr1)
			{
				char_count++;
				if(chr == '\n')
				{
					line_count++;
				}
				chr = read_file.get();
				chr1 = read_file1.get();
			}
			s_char = char_count;
			loc_base->add_location(f_char,s_char,line_count);
			
		}
		
	}
	loc_base->display_list();
	loc_base->output();
	
	system("PAUSE");
	return 0;
}