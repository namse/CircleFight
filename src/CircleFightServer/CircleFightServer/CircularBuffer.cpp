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

	/// A, B 영역 둘다 데이터가 있는 경우는 A먼저 읽는다
	if ( a_region_size_ > 0 )
	{
		a_read_size = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		memcpy(destbuf, a_region_pointer_, a_read_size) ;
		cnt -= a_read_size ;
	}

	/// 읽기 요구한 데이터가 더 있다면 B 영역에서 읽는다
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		assert(cnt <= b_region_size_) ;

		/// 남은거 마저 다 읽기
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


	/// A, B 영역 둘다 데이터가 있는 경우는 A먼저 읽는다
	if ( a_region_size_ > 0 )
	{
		a_read_size = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		memcpy(destbuf, a_region_pointer_, a_read_size) ;
		a_region_size_ -= a_read_size ;
		a_region_pointer_ += a_read_size ;
		cnt -= a_read_size ;
	}
	
	/// 읽기 요구한 데이터가 더 있다면 B 영역에서 읽는다
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		assert(cnt <= b_region_size_) ;

		/// 남은거 마저 다 읽기
		size_t b_read_size = cnt ;

		memcpy(destbuf+a_read_size, b_region_pointer_, b_read_size) ;
		b_region_size_ -= b_read_size ;
		b_region_pointer_ += b_read_size ;
		cnt -= b_read_size ;
	}

	assert( cnt == 0 ) ;

	/// A 버퍼가 비었다면 B버퍼를 맨 앞으로 당기고 A 버퍼로 지정 
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
			/// B에 아무것도 없는 경우 그냥 A로 스위치
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

	/// Read와 반대로 B가 있다면 B영역에 먼저 쓴다
	if( b_region_pointer_ != nullptr )
	{
		if ( GetBFreeSpace() < bytes )
			return false ;

		memcpy(b_region_pointer_ + b_region_size_, data, bytes) ;
		b_region_size_ += bytes ;

		return true ;
	}

	/// A영역보다 다른 영역의 용량이 더 클 경우 그 영역을 B로 설정하고 기록
	if ( GetAFreeSpace() < GetSpaceBeforeA() )
	{
		AllocateB() ;

		if ( GetBFreeSpace() < bytes )
			return false ;

		memcpy(b_region_pointer_ + b_region_size_, data, bytes) ;
		b_region_size_ += bytes ;

		return true ;
	}
	/// A영역이 더 크면 당연히 A에 쓰기
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
	
	/// Read와 마찬가지로 A가 있다면 A영역에서 먼저 삭제

	if ( a_region_size_ > 0 )
	{
		size_t aRemove = (cnt > a_region_size_) ? a_region_size_ : cnt ;
		a_region_size_ -= aRemove ;
		a_region_pointer_ += aRemove ;
		cnt -= aRemove ;
	}

	// 제거할 용량이 더 남은경우 B에서 제거 
	if ( cnt > 0 && b_region_size_ > 0 )
	{
		size_t bRemove = (cnt > b_region_size_) ? b_region_size_ : cnt ;
		b_region_size_ -= bRemove ;
		b_region_pointer_ += bRemove ;
		cnt -= bRemove ;
	}

	/// A영역이 비워지면 B를 A로 스위치 
	if ( a_region_size_ == 0 )
	{
		if ( b_region_size_ > 0 )
		{
			/// 앞으로 당겨 붙이기
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


