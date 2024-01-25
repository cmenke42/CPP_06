#ifndef OUTPUT_HPP_INCLUDED
# define OUTPUT_HPP_INCLUDED

class Output
{
	public:
		Output();
		Output(const Output& other);
		Output& operator=(const Output& other);
		~Output();

		void  	setChar(char c);
		void  	setInt(int i);
		void  	setFloat(float f);
		void  	setDouble(double d);

		void  	setFractionalPartSize(int size);

		char 	getChar() const;
		int 	getInt() const;
		float 	getFloat() const;
		double 	getDouble() const;

		bool	isDoubleSet() const;

		void  	print() const;
		void  	printChar() const;
		void  	printInt() const;
		void  	printFloat() const;
		void  	printDouble() const;

	private:
		bool 	_valueSet;
		char 	_char;
		bool 	_charSet;
		int 	_int;
		bool 	_intSet;
		int 	_fractionalPartSize;
		float 	_float;
		bool 	_floatSet;
		double 	_double;
		bool 	_doubleSet;
};

#endif /* OUTPUT_HPP_INCLUDED */
