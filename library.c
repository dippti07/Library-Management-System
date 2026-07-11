/* Title: Library Management System
   Author: Dippti Sharma
   Roll no.: 25EBKCS024
   Team name: cosmic coders 
   College: BK Birla Institute of Engineering and Technology,Pilani.
   Abstract: This is a simple Library Management System implemented in C. It allows users to add books, search and issue books, return books, and view the list of available books in the library. The system maintains records of issued books and ensures that the library's capacity is not exceeded. The program uses structures to store book details and issue records, and provides a user-friendly menu interface for interaction.
   Approach: The program defines two main structures: Book and Issue. The Book structure holds details about each book, including its ID, name, author, and quantity. The Issue structure keeps track of which student has issued which book. The program maintains an array of books and an array of issued records. It provides functions to add new books, search for books by ID, issue books to students, return books, and view all available books. The main function presents a menu to the user and calls the appropriate functions based on the user's choice.
   */

#include <stdio.h>

/* ============================================================
   STRUCT DEFINITIONS
   ============================================================ */

// Book struct - ek book ki saari details store karega
struct Book
{
    int bookid;         // book ka unique id
    char bookname[50];  // book ka naam
    char author[50];    // author ka naam
    int quantity;       // us book ki kitni copies available hain
};

struct Book library[100]; // library array - max 100 book entries store kar sakta hai

int totalbooks = 0; // ye quantity ka total hai jo library me hai (sab books ki total copies)
int viewbook = 0;   // ye kitne types of books add hue hai library me (unique book entries ka count)

// Issue struct - kisi student ko kaunsi book issue hui hai uska record
struct Issue
{
    int studentid; // jis student ne book issue karayi
    int bookid;    // kaunsi book issue hui
};
struct Issue details[100]; // issued books ka record array
int totalissue = 0;        // total kitni books abhi issue hui hui hain (returned nahi hui)

/* ============================================================
   FUNCTION: lines
   Kaam: screen pe "=" ki n lines print karta hai (design/decoration ke liye)
   ============================================================ */
void lines(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("="); // ek "=" print karo, loop n baar chalega
    }
}

/* ============================================================
   FUNCTION: add_book
   Kaam: naye book ki entry library array me add karta hai
   ============================================================ */
void add_book()
{
    printf("\n\n\n------------------------ ADD BOOKS --------------------------\n");
    lines(61); // header ke niche separator line

    char c; // user se pucha jayega ki aur book add karni hai ya nahi (Y/N)

    do
    {
        int bookid;

        // agar library full ho chuki hai (100 books ho gyi) to aur add nahi kar sakte
        if (totalbooks >= 100)
        {
            printf("\nLibrary Full\n");
            return; // function se bahar nikal jao
        }

        printf("\nEnter Book Id :\t");
        scanf("%d", &bookid); // user se book id lo

        // check karo ki ye book id pehle se to exist nahi karti
        for (int i = 0; i < viewbook; i++)
        {
            if (library[i].bookid == bookid)
            {
                printf("\nBook Already Exists!\n");
                return; // agar duplicate mila to function band karo
            }
        }

        library[viewbook].bookid = bookid; // naya book id store karo

        printf("\nEnter Book Name : \t");
        scanf(" %[^\n]", library[viewbook].bookname); // space wale naam ke liye %[^\n] use kiya (poori line padhega)

        printf("\nEnter Author Name : \t");
        scanf(" %[^\n]", library[viewbook].author); // author ka naam bhi same tarike se

        printf("\nEnter Quantity(Remaining : %d) : \t", 100 - totalbooks); // kitni jagah bachi hai library me wo dikhaya
        scanf("%d", &library[viewbook].quantity);

        // quantity 0 ya negative nahi honi chahiye
        if (library[viewbook].quantity <= 0)
        {
            printf("\n\nInvalid Quantity!\n");
            return;
        }

        // agar total capacity (100) exceed ho rahi hai to allow mat karo
        if (totalbooks + library[viewbook].quantity > 100)
        {
            printf("\nInvalid Quantity! Library Capacity Exceeded.\n");
            return;
        }

        totalbooks += library[viewbook].quantity; // total books count update karo
        viewbook++;                               // ek naya unique book entry add ho gaya, counter badhao

        printf("\nTotal Books in Library : %d", totalbooks);

        printf("\n");
        lines(61);
        printf("\n\t\t  Book Added Successfully\n"); // success message
        lines(61);
        printf("\n");

        printf("\nDo You Want to Add Another Book? (Y/N): ");
        scanf(" %c", &c); // user ka response lo (Y/N)

    } while (c == 'Y' || c == 'y'); // jab tak user 'Y' bole, loop chalta rahega
}

/* ============================================================
   FUNCTION: search_and_issue_book
   Kaam: book id se search karta hai aur agar available ho to issue karta hai
   ============================================================ */
void search_and_issue_book()
{
    char again; // dobara search karna hai ya nahi, uske liye

    do
    {
        printf("\n\n\n----------------------- SEARCH BOOK -------------------------\n");
        lines(61);

        int bookid;
        printf("\nEnter Book Id : ");
        scanf("%d", &bookid); // user se search karne wali book id lo

        int found = 0; // flag - book mili ya nahi track karne ke liye

        // pura library array traverse karke book dhoondo
        for (int i = 0; i < viewbook; i++)
        {
            if (library[i].bookid == bookid)
            {
                found = 1; // book mil gayi

                // book ki details print karo
                printf("\nBook Id : %d\n", library[i].bookid);
                printf("Book Name : %s\n", library[i].bookname);
                printf("Author Name : %s\n", library[i].author);
                printf("Quantity : %d\n", library[i].quantity);

                // agar quantity available hai tabhi issue kar sakte hain
                if (library[i].quantity > 0)
                {
                    printf("\t\t    Available for issue\n");
                    lines(61);
                    printf("\n");

                    char issue;
                    printf("Issue this book ? [Y/N] : ");
                    scanf(" %c", &issue); // user se pucho issue karni hai kya
                    printf("\n");

                    if (issue == 'Y' || issue == 'y')
                    {
                        printf("Enter Student id : ");
                        scanf("%d", &details[totalissue].studentid); // student id lo
                        details[totalissue].bookid = library[i].bookid; // issue record me book id daalo

                        printf("\n");
                        lines(61);
                        printf("\n\t\t    ISSUED SUCCESSFULLY\n"); // success message
                        lines(61);
                        printf("\n");

                        library[i].quantity--; // is book ki ek copy kam ho gayi
                        totalbooks--;           // total books me se bhi ek kam karo
                        totalissue++;           // issue record ka count badhao
                    }
                }
            }
        }

        // agar book id match nahi hui kisi se
        if (found == 0)
        {
            printf("\nBook not found!\n");
        }

        printf("\nDo you want to search again [Y/N] ?");
        scanf(" %c", &again); // dobara search karni hai kya
    } while (again == 'Y' || again == 'y'); // jab tak Y/y ho, loop chalta rahega
}

/* ============================================================
   FUNCTION: return_book
   Kaam: student ke return kiye hue book ka record update karta hai
   ============================================================ */
void return_book()
{
    printf("\n\n\n----------------------- RETURN BOOK -------------------------\n");
    lines(61);

    char again;
    int id, bookid;

    do
    {
        printf("\nEnter Student Id : \t");
        scanf("%d", &id); // student id lo

        printf("\nEnter Book Id : \t");
        scanf("%d", &bookid); // book id lo
        printf("\n");

        int found = 0; // flag - match mila ya nahi

        // issue list me se dhoondo ki is student ne ye book li thi ya nahi
        for (int i = 0; i < totalissue; i++)
        {
            for (int j = 0; j < viewbook; j++)
            {
                // teeno condition match honi chahiye: student id, book id (issue record) aur library me wahi book id
                if (details[i].studentid == id && details[i].bookid == bookid && library[j].bookid == bookid)
                {
                    found = 1;

                    printf("\n\t\t     -- ISSUED BOOK --\n");
                    lines(61);
                    printf("\nBook Name : %s\n", library[j].bookname);
                    printf("Author : %s\n", library[j].author);

                    library[j].quantity++; // book wapas aane se quantity badha do

                    // issue record se ye entry remove karni hai, isliye aage wali entries ko peeche shift karo
                    for (int k = i; k < totalissue - 1; k++)
                    {
                        details[k] = details[k + 1];
                    }

                    totalbooks++;  // total books me ek book wapas add ho gayi
                    totalissue--;  // ek issue record kam ho gaya

                    lines(61);
                    printf("\n\t\t  BOOK RETURNED SUCCESSFULLY\n"); // success message
                    lines(61);
                    printf("\n");
                    break; // andar wala loop tod do, kaam ho gaya
                }
            }
        }

        // agar match hi nahi mila to matlab book issue hi nahi thi
        if (found == 0)
        {
            printf("\n-- Book Not Issued! --\n\n");
        }

        lines(61);
        printf("\nDo you want to Return another book [Y/N] ? ");
        scanf(" %c", &again); // dobara return karna hai kya
    } while (again == 'Y' || again == 'y'); // jab tak Y/y ho
}

/* ============================================================
   FUNCTION: view_book
   Kaam: library me maujood saari books ki list print karta hai
   ============================================================ */
void view_book()
{
    printf("\n\n\n----------------------- VIEW BOOKS --------------------------\n");
    lines(61);

    // agar library khali hai to seedha message dikha do
    if (totalbooks == 0)
    {
        printf("\nNo Books in Library.\n");
        return;
    }

    printf("\n");
    lines(61);

    // har book entry ko loop karke print karo
    for (int i = 0; i < viewbook; i++)
    {
        printf("\n\nBook ID : %d", library[i].bookid);
        printf("\nBook Name : %s", library[i].bookname);
        printf("\nAuther Name : %s", library[i].author);
        printf("\nOuantity : %d\n\n", library[i].quantity);
        lines(61); // har book ke baad ek separator line
    }

    printf("\n");
    lines(61);
    printf("\n");
}

/* ============================================================
   FUNCTION: main
   Kaam: menu dikhata hai aur user ke choice ke hisaab se
         upar wale functions ko call karta hai
   ============================================================ */
int main()
{
    int f; // user ka menu choice store karne ke liye

    do
    {
        // menu header print karo
        lines(61);
        printf("\n\t\tLIBRARY MANAGEMENT SYSTEM\n");
        lines(61);

        // menu options dikhao
        printf("\n\n1. Add Book\n2. Search & Issue Book\n3. Return Book\n4. View Books\n5. Exit\n\n");
        lines(61);

        printf("\nEnter Your Choice :\t");
        scanf("%d", &f); // user ka choice lo

        // choice ke hisaab se sahi function call karo
        switch (f)
        {
        case 1:
            add_book(); // neya book add karne ke liye
            printf("\n\n\n");
            break;

        case 2:
            search_and_issue_book(); // book search + issue karne ke liye
            printf("\n\n\n");
            break;

        case 3:
            return_book(); // book return karne ke liye
            printf("\n\n\n");
            break;

        case 4:
            view_book(); // saari books dekhne ke liye
            printf("\n\n\n");
            break;

        case 5:
            // program band karne wala option
            printf("\n\n\n");
            lines(61);
            printf("\n\tThank You for Using Library Management System.\n");
            lines(61);
            printf("\n\n\n");
            break;

        default:
            // agar user ne 1-5 ke alawa kuch aur dala
            printf("\n\nChoose a valid option\n\n");
            printf("\n\n\n");
            break;
        }
    } while (f != 5); // jab tak user 5 (Exit) na choose kare, loop chalta rahega

    return 0; // program successfully khatam
}