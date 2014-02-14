#include "stdafx.h"
#include "CircularBuffer.h"
#include <assert.h>


bool CircularBuffer::Peek(OUT char* destbuf, size_t bytes) const
{
	assert( buffer_ != nullptr ) ;

	if( a_region_size_ + b_region_size_ < bytes )
		return false ;

	size_t cnt = bytes ;
	size_t a_read_size = 0 ;

	/// A, B ���� �Ѵ� �����Ͱ� �ִ� ���� A���� �д´�
	if ( a_region_size_ > 0 )
	{
		a_read_size = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		memcpy(destbuf, a_region_pointer_, a_read_size) ;
		cnt -= a_read_size ;
	}

	/// �б� �䱸�� �����Ͱ� �� �ִٸ� B �������� �д´�
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		assert(cnt <= b_region_size_) ;

		/// ������ ���� �� �б�
		size_t b_read_size = cnt ;

		memcpy(destbuf+a_read_size, b_region_pointer_, b_read_size) ;
		cnt -= b_read_size ;
	}

	assert( cnt == 0 ) ;

	return true ;

}

bool CircularBuffer::Read(OUT char* destbuf, size_t bytes)
{
	assert( buffer_ != nullptr ) ;

	if( a_region_size_ + b_region_size_ < bytes )
		return false ;

	size_t cnt = bytes ;
	size_t a_read_size = 0 ;


	/// A, B ���� �Ѵ� �����Ͱ� �ִ� ���� A���� �д´�
	if ( a_region_size_ > 0 )
	{
		a_read_size = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		memcpy(destbuf, a_region_pointer_, a_read_size) ;
		a_region_size_ -= a_read_size ;
		a_region_pointer_ += a_read_size ;
		cnt -= a_read_size ;
	}
	
	/// �б� �䱸�� �����Ͱ� �� �ִٸ� B �������� �д´�
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		assert(cnt <= b_region_size_) ;

		/// ������ ���� �� �б�
		size_t b_read_size = cnt ;

		memcpy(destbuf+a_read_size, b_region_pointer_, b_read_size) ;
		b_region_size_ -= b_read_size ;
		b_region_pointer_ += b_read_size ;
		cnt -= b_read_size ;
	}

	assert( cnt == 0 ) ;

	/// A ���۰� ����ٸ� B���۸� �� ������ ���� A ���۷� ���� 
	if ( a_region_size_ == 0 )
	{
		if ( b_region_size_ > 0 )
		{
			if ( b_region_pointer_ != buffer_ )
				memmove(buffer_, b_region_pointer_, b_region_size_) ;

			a_region_pointer_ = buffer_ ;
			a_region_size_ = b_region_size_ ;
			b_region_pointer_ = nullptr ;
			b_region_size_ = 0 ;
		}
		else
		{
			/// B�� �ƹ��͵� ���� ��� �׳� A�� ����ġ
			b_region_pointer_ = nullptr ;
			b_region_size_ = 0 ;
			a_region_pointer_ = buffer_ ;
			a_region_size_ = 0 ;
		}
	}

	return true ;
}




bool CircularBuffer::Write(const char* data, size_t bytes)
{
	assert( buffer_ != nullptr ) ;

	/// Read�� �ݴ�� B�� �ִٸ� B������ ���� ����
	if( b_region_pointer_ != nullptr )
	{
		if ( GetBFreeSpace() < bytes )
			return false ;

		memcpy(b_region_pointer_ + b_region_size_, data, bytes) ;
		b_region_size_ += bytes ;

		return true ;
	}

	/// A�������� �ٸ� ������ �뷮�� �� Ŭ ��� �� ������ B�� �����ϰ� ���
	if ( GetAFreeSpace() < GetSpaceBeforeA() )
	{
		AllocateB() ;

		if ( GetBFreeSpace() < bytes )
			return false ;

		memcpy(b_region_pointer_ + b_region_size_, data, bytes) ;
		b_region_size_ += bytes ;

		return true ;
	}
	/// A������ �� ũ�� �翬�� A�� ����
	else
	{
		if ( GetAFreeSpace() < bytes )
			return false ;

		memcpy(a_region_pointer_ + a_region_size_, data, bytes) ;
		a_region_size_ += bytes ;

		return true ;
	}
}



void CircularBuffer::Remove(size_t len)
{
	size_t cnt = len ;
	
	/// Read�� ���������� A�� �ִٸ� A�������� ���� ����

	if ( a_region_size_ > 0 )
	{
		size_t aRemove = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		a_region_size_ -= aRemove ;
		a_region_pointer_ += aRemove ;
		cnt -= aRemove ;
	}

	// ������ �뷮�� �� ������� B���� ���� 
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		size_t bRemove = (cnt > b_region_size_) ? b_region_size_ : cnt ;
		b_region_size_ -= bRemove ;
		b_region_pointer_ += bRemove ;
		cnt -= bRemove ;
	}

	/// A������ ������� B�� A�� ����ġ 
	if ( a_region_size_ == 0 )
	{
		if ( b_region_size_ > 0 )
		{
			/// ������ ��� ���̱�
			if ( b_region_pointer_ != buffer_ )
				memmove(buffer_, b_region_pointer_, b_region_size_) ;
	
			a_region_pointer_ = buffer_ ;
			a_region_size_ = b_region_size_ ;
			b_region_pointer_ = nullptr ;
			b_region_size_ = 0 ;
		}
		else
		{
			b_region_pointer_ = nullptr ;
			b_region_size_ = 0 ;
			a_region_pointer_ = buffer_ ;
			a_region_size_ = 0 ;
		}
	}
}


