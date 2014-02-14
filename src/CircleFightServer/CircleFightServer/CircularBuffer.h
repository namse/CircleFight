#pragma once


class CircularBuffer
{
public:

	CircularBuffer(size_t capacity) : b_region_pointer_(nullptr), a_region_size_(0), b_region_size_(0)
	{
		buffer_ = new char[capacity] ;
		buffer_end_ = buffer_ + capacity ;
		a_region_pointer_ = buffer_ ;
	}

	~CircularBuffer()
	{
		delete [] buffer_ ;
	}

	bool Peek(OUT char* destbuf, size_t bytes) const ;
	bool Read(OUT char* destbuf, size_t bytes) ;
	bool Write(const char* data, size_t bytes) ;


	/// ������ ù�κ� len��ŭ ������
	void Remove(size_t len) ;

	size_t GetFreeSpaceSize()
	{
		if ( b_region_pointer_ != nullptr )
			return GetBFreeSpace() ;
		else
		{
			/// A ���ۺ��� �� ���� �����ϸ�, B ���۷� ����ġ
			if ( GetAFreeSpace() < GetSpaceBeforeA() )
			{
				AllocateB() ;
				return GetBFreeSpace() ;
			}
			else
				return GetAFreeSpace() ;
		}
	}

	size_t GetStoredSize() const
	{
		return a_region_size_ + b_region_size_ ;
	}

	size_t GetContiguiousBytes() const 
	{
		if ( a_region_size_ > 0 )
			return a_region_size_ ;
		else
			return b_region_size_ ;
	}

	/// ���Ⱑ ������ ��ġ (������ ���κ�) ��ȯ
	void* GetBuffer() const
	{
		if( b_region_pointer_ != nullptr )
			return b_region_pointer_ + b_region_size_ ;
		else
			return a_region_pointer_ + a_region_size_ ;
	}

	


	/// Ŀ��(aka. IncrementWritten)
	void Commit(size_t len)
	{
		if ( b_region_pointer_ != nullptr )
			b_region_size_ += len ;
		else
			a_region_size_ += len ;
	}

	/// ������ ù�κ� ����
	void* GetBufferStart() const
	{
		if ( a_region_size_ > 0 )
			return a_region_pointer_ ;
		else
			return b_region_pointer_ ;
	}


private:

	void AllocateB()
	{
		b_region_pointer_ = buffer_ ;
	}

	size_t GetAFreeSpace() const
	{ 
		return (buffer_end_ - a_region_pointer_ - a_region_size_) ; 
	}

	size_t GetSpaceBeforeA() const
	{ 
		return (a_region_pointer_ - buffer_) ; 
	}


	size_t GetBFreeSpace() const
	{ 
		if (b_region_pointer_ == nullptr)
			return 0 ; 

		return (a_region_pointer_ - b_region_pointer_ - b_region_size_) ; 
	}

private:

	char*	buffer_ ;
	char*	buffer_end_ ;

	char*	a_region_pointer_ ;
	size_t	a_region_size_ ;

	char*	b_region_pointer_ ;
	size_t	b_region_size_ ;

} ;
