def main():
    filename = input("Enter a filename: ")
    try:
        huff = open(filename,"r")
    except:
        print "File does not exist in current directory" , IOError
        main()
    huffTxt = huff.read()
    freqs = {}
    for char in huffTxt:
        if char in freqs:
            freqs[char] += 1
        else:
            freqs[char] = 1
    print " There are %s bytes in the file " % len(huffTxt)
    print " There are %s different characters in the file" % len(freqs)
    print freqs
    huff.close()
    

from Tkinter import *
    
Tk = Tk()
Tk.configure(background = 'black')
Tk.title("Huffman")
filenames = StringVar()
Enter = Entry(Tk,textvariable = filenames)
B1 = Button(Tk, text = "click to use Huffman on the above file",command = main)




Enter.pack()
B1.pack()
Tk.mainloop()
    
if __name__ == "__main__":
    main()
