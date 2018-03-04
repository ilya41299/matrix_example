#include "matrix.hpp"

matrix_t::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

matrix_t::matrix_t( matrix_t const & other )
{
	rows_ = other.rows_;
	collumns_ = other.collumns_;
	elements_ = new float *[ rows_];
	for (std::size_t i = 0; i <  rows_; ++i) {
	elements_[i] = new float[collumns_];
		for (std::size_t j = 0; j < collumns_; ++j) {
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

matrix_t & matrix_t::operator =( matrix_t const & other )
{
	if (this != &other)
	{
		if (elements_ != nullptr && rows_  && columns_)
		{
			for (std::size_t i = 0; i < rows_; ++i)
			{
				delete[] elements_[i];
			}
			delete[] elements_;
		}
		rows_ = other.rows_;
		columns_ = other.columns_;
		elements_ = new int*[rows_];
		for (std::size_t i = 0; i < rows_; ++i)
		{
			elements_[i] = new int[columns_];
			for (std::size_t j = 0; j < columns_; ++j)
			{
				elements_[i][j] = other.elements_[i][j];
			}
		}
		return *this;
}

matrix_t::~matrix_t()
{
	for (std::size_t i = 0; i < this->rows_; i++)
        {
            delete[] this->elements_[i];
        }
        delete[] this->elements_;
        columns_ = 0;
        rows_ = 0;
}

std::size_t matrix_t::rows() const
{
    return rows_;
}

std::size_t matrix_t::collumns() const
{
    return collumns_;
}

matrix_t matrix_t::operator +( matrix_t const & other ) const
{
	 matrix_t result;
        if (this->rows_ == other.rows_ && this->columns_ == other.columns_)
        {
            result.rows_ = this->rows_;
            result.columns_ = this->columns_;
            result.elements_ = new int*[rows_];
            for (std::size_t i = 0; i < rows_; i++)
            {
                result.elements[i] = new int[columns_];
                for (std::size_t j = 0; j < columns_; j++)
                {
                    result.elements[i][j] = this->elements[i][j] + other.elements[i][j];
                }
            }
        }
        else
        {
            std::cout << "An error has occured while reading input data";
             std::endl;
        }
        return result;
}

matrix_t matrix_t::operator -( matrix_t const & other ) const
{
	 matrix_t result;
        if (this->rows_ == other.rows_ && this->columns_ == other.columns_)
        {
            result.rows_ = this->rows_;
            result.columns_ = this->columns_;
            result.elements_ = new int*[rows_];
            for (std::size_t i = 0; i < rows_; i++)
            {
                result.elements_[i] = new int[columns_];
                for (std::size_t j = 0; j < columns_; j++)
                {
                    result.elements_[i][j] = this->elements_[i][j] - other.elements_[i][j];
                }
            }
        }
        else
        {
             std::cout << "An error has occured while reading input data";
             std::endl;
        }
        return result;
}

matrix_t matrix_t::operator *( matrix_t const & other ) const
{
	matrix_t result;
        if (this->columns_ == other.rows_)
        {
            result.rows_ = this->rows_;
            float sum = 0;
            result.columns_ = other.columns_;
            result.elements_ = new int*[result.rows_];
            for (std::size_t i = 0; i < result.rows_; ++i)
            {
                result.data[i] = new int[result.columns_];
                for (std::size_t j = 0; j < result.columns_; ++j)
                {
                    sum = 0;
                    for (std::size_t k = 0; k < this->columns_; ++k)
                    {
                        sum += this->elements_[i][k] * other.elements_[k][j];
                    }
                    result.elements_[i][j] = sum;
                }
            }
        }
        else
        {
            std::cout << "An error has occured while reading input data";
             std::endl;
        }
        return result;
}

matrix_t & matrix_t::operator -=( matrix_t const & other )
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		for (std::size_t i = 0; i<rows_; i++) {
			for (std::size_t j = 0; j<collumns_; j++) {
				elements_[i][j] -= other.elements_[i][j];
			}
		}
	}
	else {
		std::cout << "An error has occured while reading input data";
             std::endl;
	}
	
	return *this;
}

matrix_t & matrix_t::operator +=( matrix_t const & other )
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		for (std::size_t i = 0; i<rows_; i++) {
			for (std::size_t j = 0; j<collumns_; j++) {
				elements_[i][j] += other.elements_[i][j];
			}
		}
	}
	else {
		 std::cout << "An error has occured while reading input data";
             std::endl;
	}
	
	return *this;
}

matrix_t & matrix_t::operator *=( matrix_t const & other )
{
	matrix_t result;
	
	if (collumns_ == other.rows_) {
		result.elements_ = new float *[rows_];
		for (std::size_t i = 0; i<rows_; i++) {
			result.elements_[i] = new float [other.collumns_];
	    }
	    result.rows_ = rows_;
	    result.collumns_ = other.collumns_;
	    
		for (std::size_t i = 0; i < rows_; ++i) {
			for (std::size_t j = 0; j < other.collumns_; ++j) {
				int result_ = 0;
				for (std::size_t k = 0; k < other.rows_; ++k) {
					result_ += elements_[i][k] * other.elements_[k][j];
				}
				result.elements_[i][j] = result_;
			}
		}
		*this = result;
	}
	else {
		std::cout << "An error has occured while reading input data";
             std::endl;
	}
	
	return *this;
}

std::istream & matrix_t::read( std::istream & stream )
{
    std::size_t rows;
    std::size_t collumns;
    char symbol;
    
    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) {
        float ** elements = new float *[ rows ];
        for( std::size_t i = 0; success && i < rows; ++i ) {
            elements[ i ] = new float[ collumns ];
            for( std::size_t j = 0; j < collumns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) {
            for( std::size_t i = 0; i < rows_; ++i ) {
                delete [] elements_[ i ];
            }
            delete [] elements_;
            
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else {
            for( std::size_t i = 0; i < rows; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else {
        success = false;
    }
    
    if( !success ) {
        stream.setstate( std::ios_base::failbit );
    }
    
	return stream;
}

std::ostream & matrix_t::write( std::ostream & stream ) const
{
    stream << rows_ << ", " << collumns_;
    for( std::size_t i = 0; i < rows_; ++i ) {
        stream << '\n';
        for( std::size_t j = 0; j < collumns_; ++j ) {
            stream << elements_[ i ][ j ];
            if( j != rows_ - 1 ) {
                stream << ' ';
            }
        }
    }
    
	return stream;
}
