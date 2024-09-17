/* BEGIN IFRAME FASTIO */

#include <cstdlib>
#include <cstdint>
#include <cstdio>

#include <string>

#define BUF_SZ 4096

struct fastio{
	char stdout_buffer[BUF_SZ],
		 stdin_buffer[BUF_SZ];

	uint64_t buffer_size = BUF_SZ,
			 stdout_pos,
			 stdin_pos;

	bool line_buffer = 1;

	inline void fast() { line_buffer = 0; }

	inline void write(){
		fwrite(stdout_buffer, 1, stdout_pos, stdout);
		stdout_pos = 0;
	}

	inline void write_char(const char c){
		if(stdout_pos == buffer_size) write();
		stdout_buffer[stdout_pos++] = c;
		if(line_buffer && c == '\n') write();
	}

	fastio &operator<<(unsigned int i){
		char buf[11];
		uint32_t sz = 0;
		do buf[sz++] = '0' + i%10, i /= 10;
		while(i);
		while(sz) write_char(buf[--sz]);
		return *this;
	}

	fastio &operator<<(int i){
		if(i<0) write_char('-'), i = -i;
		char buf[11];
		uint32_t sz = 0;
		do buf[sz++] = '0' + i%10, i /= 10;
		while(i);
		while(sz) write_char(buf[--sz]);
		return *this;
	}

	fastio &operator<<(unsigned long long i){
		char buf[22];
		uint32_t sz = 0;
		do buf[sz++] = '0' + i%10, i /= 10;
		while(i);
		while(sz) write_char(buf[--sz]);
		return *this;
	}

	fastio &operator<<(long long i){
		if(i<0) write_char('-'), i = -i;
		char buf[22];
		uint32_t sz = 0;
		do buf[sz++] = '0' + i%10, i /= 10;
		while(i);
		while(sz) write_char(buf[--sz]);
		return *this;
	}

	fastio &operator<<(double i){
		char buf[50]; sprintf(buf, "%f", i);
		this[0] << buf;
		return *this;
	}

	fastio &operator<<(char i){
		write_char(i);
		return *this;
	}

	fastio &operator<<(char *i){
		while(*i) write_char(*(i++));
		return *this;
	}

	fastio &operator<<(const char *i){
		while(*i) write_char(*(i++));
		return *this;
	}

	fastio &operator<<(std::string s){
		for(char x : s) write_char(x);
		return *this;
	}

	inline void read(){
		stdin_pos = 0;
		fgets(stdin_buffer, buffer_size, stdin);
	}

	inline char peek_char(){
		if(!stdin_buffer[stdin_pos]) read();
		return stdin_buffer[stdin_pos];
	}

	inline char read_char(){
		char ret = peek_char();
		++stdin_pos;
		return ret;
	}

	inline bool is_whitespace(char i){
		if(i == ' ') return 1;
		if(i == '\n') return 1;
		if(i == '\t') return 1;
		return 0;
	}

	inline bool is_digit(char i){
		return i >= '0' && i <= '9';
	}

	inline void flush_stdin() { while(is_whitespace(peek_char())) read_char(); }

	fastio &operator>>(int &i){
		flush_stdin();
		int sign = 1;
		if(peek_char() == '-') read_char(), sign = -1;
		uint32_t build = 0;
		while(is_digit(peek_char())) build = build*10 + read_char()-'0';
		i = sign * build;
		return *this;
	}

	fastio &operator>>(unsigned int &i){
		flush_stdin();
		uint32_t build = 0;
		while(is_digit(peek_char())) build = build*10 + read_char()-'0';
		i = build;
		return *this;
	}

	fastio &operator>>(long long &i){
		flush_stdin();
		long long sign = 1;
		if(peek_char() == '-') read_char(), sign = -1;
		uint64_t build = 0;
		while(is_digit(peek_char())) build = build*10 + read_char()-'0';
		i = sign * build;
		return *this;
	}

	fastio &operator>>(unsigned long long &i){
		flush_stdin();
		uint64_t build = 0;
		while(is_digit(peek_char())) build = build*10 + read_char()-'0';
		i = build;
		return *this;
	}

	fastio &operator>>(char &i){
		flush_stdin();
		i = read_char();
		return *this;
	}

	fastio &operator>>(std::string &i){
		flush_stdin();
		i.clear();
		while(!is_whitespace(peek_char()))
			i += read_char();
		return *this;
	}

	fastio &operator>>(float &i){
		flush_stdin();
		float sign = 1;
		if(peek_char() == '-') sign = -1, read_char();
		unsigned int int_part; this[0] >> int_part;
		if(peek_char() == '.') read_char();
		else{ i = sign * int_part; return *this; }
		float ret = int_part, pow = 0.1;
		while(is_digit(peek_char()))
			ret += pow * (read_char()-'0'),
				pow /= 10;
		i = sign * ret;
		return *this;
	}

	fastio &operator>>(double &i){
		flush_stdin();
		double sign = 1;
		if(peek_char() == '-') sign = -1, read_char();
		unsigned long long int_part; this[0] >> int_part;
		if(peek_char() == '.') read_char();
		else{ i = sign * int_part; return *this; }
		double ret = int_part, pow = 0.1;
		while(is_digit(peek_char()))
			ret += pow * (read_char()-'0'),
				pow /= 10;
		i = sign * ret;
		return *this;
	}

	inline void getline(std::string &i){
		flush_stdin();
		while(peek_char() != '\n') i += read_char();
	}

	~fastio() { write(); }
};

inline fastio io;

/* END IFRAME FASTIO */

int main(){
	io.fast();  // disables line buffering; optional
	
	io << "hello world" << '\n';
	io << 3.1415926 << '\n';
	io << 1234 << ' ' << -34233 << "\n\n";

	std::string s = "c++ strings work!";
	io << s << "\n\n";

	io << "input works too: (enter an int) ", io.write();  // flushes stdout, we didn't newline

	long long n; io >> n;
	io << "got: " << n << "\n\n";

	io << "now a char: ", io.write();

	char c; io >> c;
	io << "got: " << c << "\n\n";

	io << "now a float: ", io.write();

	double f; io >> f;
	io << "got: " << f << "\n\n";

	io << "or a string: ", io.write();

	std::string str; io >> str;
	io << "got: " << str << "\n\n";

	io << "grab a whole line: ", io.write();

	std::string line; io.getline(line);
	io << "got: " << line << '\n';
}
