#include <string>


namespace Gerald
{
	class String
	{
	public:
		String(const char *str = "");
		~String();
		String(const char& str);
		String& operator= (String s);

		void push_back(char ch);
		void append(const char *str);
		String& operator+= (char ch);
		String& operator+= (const char *str);
		size_t find(char ch, size_t pos = 0);
		size_t find(const char *str, size_t pos = 0);
		void Insert(size_t pos, char ch);
		void Insert(size_t pos, const char *str);
		void Erase(size_t pos, size_t len = npos);
		void Swap(String& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		char *c_str()
		{
			return _str;
		}

		char& operator[](size_t pos);
		const char& operator[](size_t pos) const;
		size_t size() const;
		size_t capacity() const;
		void reserve(size_t n);
		void resize(size_t n, char ch = '\0');


	private:
		char *_str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	const size_t String::npos = -1;
}