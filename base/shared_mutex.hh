// Copyright Howard Hinnant 2007-2010. Distributed under the Boost
// Software License, Version 1.0. (see http://www.boost.org/LICENSE_1_0.txt)

#ifndef SHARED_MUTEX
#define SHARED_MUTEX

/*

<shared_mutex> synopsis

namespace ting
{

class shared_mutex
{
public:

	shared_mutex();
	~shared_mutex();

	shared_mutex(const shared_mutex&) = delete;
	shared_mutex& operator=(const shared_mutex&) = delete;

	// Exclusive ownership

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	// Shared ownership

	void lock_shared();
	bool try_lock_shared();
	template <class Rep, class Period>
		bool
		try_lock_shared_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_shared_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_shared();
};

class upgrade_mutex
{
public:

	upgrade_mutex();
	~upgrade_mutex();

	upgrade_mutex(const upgrade_mutex&) = delete;
	upgrade_mutex& operator=(const upgrade_mutex&) = delete;

	// Exclusive ownership

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	// Shared ownership

	void lock_shared();
	bool try_lock_shared();
	template <class Rep, class Period>
		bool
		try_lock_shared_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_shared_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_shared();

	// Upgrade ownership

	void lock_upgrade();
	bool try_lock_upgrade();
	template <class Rep, class Period>
		bool
		try_lock_upgrade_for(
							const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_upgrade_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_upgrade();

	// Shared <-> Exclusive

	bool try_unlock_shared_and_lock();
	template <class Rep, class Period>
		bool
		try_unlock_shared_and_lock_for(
							const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_unlock_shared_and_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_and_lock_shared();

	// Shared <-> Upgrade

	bool try_unlock_shared_and_lock_upgrade();
	template <class Rep, class Period>
		bool
		try_unlock_shared_and_lock_upgrade_for(
							const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_unlock_shared_and_lock_upgrade_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_upgrade_and_lock_shared();

	// Upgrade <-> Exclusive

	void unlock_upgrade_and_lock();
	bool try_unlock_upgrade_and_lock();
	template <class Rep, class Period>
		bool
		try_unlock_upgrade_and_lock_for(
							const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_unlock_upgrade_and_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_and_lock_upgrade();
};

template <class Mutex>
class shared_lock
{
public:
	typedef Mutex mutex_type;

	// Shared locking

	shared_lock();
	explicit shared_lock(mutex_type& m);
	shared_lock(mutex_type& m, std::defer_lock_t);
	shared_lock(mutex_type& m, std::try_to_lock_t);
	shared_lock(mutex_type& m, std::adopt_lock_t);
	template <class Clock, class Duration>
		shared_lock(mutex_type& m,
					const std::chrono::time_point<Clock, Duration>& abs_time);
	template <class Rep, class Period>
		shared_lock(mutex_type& m,
					const std::chrono::duration<Rep, Period>& rel_time);
	~shared_lock();

	shared_lock(shared_lock const&) = delete;
	shared_lock& operator=(shared_lock const&) = delete;

	shared_lock(shared_lock&& u);
	shared_lock& operator=(shared_lock&& u);

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	// Conversion from upgrade locking

	explicit shared_lock(upgrade_lock<mutex_type>&& u);

	// Conversion from exclusive locking

	explicit shared_lock(std::unique_lock<mutex_type>&& u);

	// Setters

	void swap(shared_lock& u);
	mutex_type* release();

	// Getters

	bool owns_lock() const;
	explicit operator bool () const;
	mutex_type* mutex() const;
};

template <class Mutex>
	void swap(shared_lock<Mutex>&  x, shared_lock<Mutex>&  y);

template <class Mutex>
class upgrade_lock
{
public:
	typedef Mutex mutex_type;

	// Upgrade locking

	upgrade_lock();
	explicit upgrade_lock(mutex_type& m);
	upgrade_lock(mutex_type& m, std::defer_lock_t);
	upgrade_lock(mutex_type& m, std::try_to_lock_t);
	upgrade_lock(mutex_type& m, std::adopt_lock_t);
	template <class Clock, class Duration>
		upgrade_lock(mutex_type& m,
					 const std::chrono::time_point<Clock, Duration>& abs_time);
	template <class Rep, class Period>
		upgrade_lock(mutex_type& m,
					 const std::chrono::duration<Rep, Period>& rel_time);
	~upgrade_lock();

	upgrade_lock(upgrade_lock const&) = delete;
	upgrade_lock& operator=(upgrade_lock const&) = delete;

	upgrade_lock(upgrade_lock&& u);
	upgrade_lock& operator=(upgrade_lock&& u);

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time);
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	// Conversion from shared locking

	upgrade_lock(shared_lock<mutex_type>&& u, try_to_lock_t);
	template <class Clock, class Duration>
		upgrade_lock(shared_lock<mutex_type>&& u,
					 const std::chrono::time_point<Clock, Duration>& abs_time);
	template <class Rep, class Period>
		upgrade_lock(shared_lock<mutex_type>&& u,
					 const std::chrono::duration<Rep, Period>& rel_time);

	// Conversion from exclusive locking

	explicit upgrade_lock(std::unique_lock<mutex_type>&& u);

	// Setters

	void swap(shared_lock& u);
	mutex_type* release();

	// Getters

	bool owns_lock() const;
	explicit operator bool () const;
	mutex_type* mutex() const;
};

template <class Mutex>
	void swap(upgrade_lock<Mutex>&  x, upgrade_lock<Mutex>&  y);

template <class ToLock, class FromLock>
class transfer_lock
{
public:
	explicit transfer_lock(FromLock& fl);
	~transfer_lock();

	transfer_lock(const transfer_lock&) = delete;
	transfer_lock& operator=(const transfer_lock&) = delete;
};

}  // ting

*/

#ifndef _LIBCPP_SHARED_LOCK
#define _LIBCPP_SHARED_LOCK
#endif

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <climits>
#include <system_error>

namespace ting {

class shared_mutex
{
	typedef std::mutex              mutex_t;
	typedef std::condition_variable cond_t;
	typedef unsigned                count_t;

	mutex_t mut_;
	cond_t  gate1_;
	cond_t  gate2_;
	count_t state_;

	static const count_t write_entered_ = 1U << (sizeof(count_t)*CHAR_BIT - 1);
	static const count_t n_readers_ = ~write_entered_;

public:
	shared_mutex();
	~shared_mutex();

	shared_mutex(const shared_mutex&) = delete;
	shared_mutex& operator=(const shared_mutex&) = delete;

// Exclusive ownership

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_until(std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

// Shared ownership

	void lock_shared();
	bool try_lock_shared();
	template <class Rep, class Period>
		bool
		try_lock_shared_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_shared_until(std::chrono::steady_clock::now() +
										 rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_shared_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_shared();
};

template <class Clock, class Duration>
bool
shared_mutex::try_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if (state_ & write_entered_)
	{
		while (true)
		{
			std::cv_status status = gate1_.wait_until(lk, abs_time);
			if ((state_ & write_entered_) == 0)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	state_ |= write_entered_;
	if (state_ & n_readers_)
	{
		while (true)
		{
			std::cv_status status = gate2_.wait_until(lk, abs_time);
			if ((state_ & n_readers_) == 0)
				break;
			if (status == std::cv_status::timeout)
			{
				state_ &= ~write_entered_;
				return false;
			}
		}
	}
	return true;
}

template <class Clock, class Duration>
bool
shared_mutex::try_lock_shared_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if ((state_ & write_entered_) || (state_ & n_readers_) == n_readers_)
	{
		while (true)
		{
			std::cv_status status = gate1_.wait_until(lk, abs_time);
			if ((state_ & write_entered_) == 0 &&
											 (state_ & n_readers_) < n_readers_)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	count_t num_readers = (state_ & n_readers_) + 1;
	state_ &= ~n_readers_;
	state_ |= num_readers;
	return true;
}

class upgrade_mutex
{
	typedef std::mutex              mutex_t;
	typedef std::condition_variable cond_t;
	typedef unsigned                count_t;

	mutex_t mut_;
	cond_t  gate1_;
	cond_t  gate2_;
	count_t state_;

	static const unsigned write_entered_ = 1U << (sizeof(count_t)*CHAR_BIT - 1);
	static const unsigned upgradable_entered_ = write_entered_ >> 1;
	static const unsigned n_readers_ = ~(write_entered_ | upgradable_entered_);

public:

	upgrade_mutex();
	~upgrade_mutex();

	upgrade_mutex(const upgrade_mutex&) = delete;
	upgrade_mutex& operator=(const upgrade_mutex&) = delete;

// Exclusive ownership

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_until(std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

// Shared ownership

	void lock_shared();
	bool try_lock_shared();
	template <class Rep, class Period>
		bool
		try_lock_shared_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_shared_until(std::chrono::steady_clock::now() +
										 rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_shared_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_shared();

// Upgrade ownership

	void lock_upgrade();
	bool try_lock_upgrade();
	template <class Rep, class Period>
		bool
		try_lock_upgrade_for(
							const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_upgrade_until(std::chrono::steady_clock::now() +
										 rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_upgrade_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_upgrade();

// Shared <-> Exclusive

	bool try_unlock_shared_and_lock();
	template <class Rep, class Period>
		bool
		try_unlock_shared_and_lock_for(
							const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_unlock_shared_and_lock_until(
								   std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_unlock_shared_and_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_and_lock_shared();

// Shared <-> Upgrade

	bool try_unlock_shared_and_lock_upgrade();
	template <class Rep, class Period>
		bool
		try_unlock_shared_and_lock_upgrade_for(
							const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_unlock_shared_and_lock_upgrade_until(
								   std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_unlock_shared_and_lock_upgrade_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_upgrade_and_lock_shared();

// Upgrade <-> Exclusive

	void unlock_upgrade_and_lock();
	bool try_unlock_upgrade_and_lock();
	template <class Rep, class Period>
		bool
		try_unlock_upgrade_and_lock_for(
							const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_unlock_upgrade_and_lock_until(
								   std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_unlock_upgrade_and_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock_and_lock_upgrade();
};

template <class Clock, class Duration>
bool
upgrade_mutex::try_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if (state_ & (write_entered_ | upgradable_entered_))
	{
		while (true)
		{
			std::cv_status status = gate1_.wait_until(lk, abs_time);
			if ((state_ & (write_entered_ | upgradable_entered_)) == 0)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	state_ |= write_entered_;
	if (state_ & n_readers_)
	{
		while (true)
		{
			std::cv_status status = gate2_.wait_until(lk, abs_time);
			if ((state_ & n_readers_) == 0)
				break;
			if (status == std::cv_status::timeout)
			{
				state_ &= ~write_entered_;
				return false;
			}
		}
	}
	return true;
}

template <class Clock, class Duration>
bool
upgrade_mutex::try_lock_shared_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if ((state_ & write_entered_) || (state_ & n_readers_) == n_readers_)
	{
		while (true)
		{
			std::cv_status status = gate1_.wait_until(lk, abs_time);
			if ((state_ & write_entered_) == 0 &&
											 (state_ & n_readers_) < n_readers_)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	count_t num_readers = (state_ & n_readers_) + 1;
	state_ &= ~n_readers_;
	state_ |= num_readers;
	return true;
}

template <class Clock, class Duration>
bool
upgrade_mutex::try_lock_upgrade_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if ((state_ & (write_entered_ | upgradable_entered_)) ||
		(state_ & n_readers_) == n_readers_)
	{
		while (true)
		{
			std::cv_status status = gate1_.wait_until(lk, abs_time);
			if ((state_ & (write_entered_ | upgradable_entered_)) == 0 &&
											 (state_ & n_readers_) < n_readers_)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	count_t num_readers = (state_ & n_readers_) + 1;
	state_ &= ~n_readers_;
	state_ |= upgradable_entered_ | num_readers;
	return true;
}

template <class Clock, class Duration>
bool
upgrade_mutex::try_unlock_shared_and_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if (state_ != 1)
	{
		while (true)
		{
			std::cv_status status = gate2_.wait_until(lk, abs_time);
			if (state_ == 1)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	state_ = write_entered_;
	return true;
}

template <class Clock, class Duration>
bool
upgrade_mutex::try_unlock_shared_and_lock_upgrade_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if ((state_ & (write_entered_ | upgradable_entered_)) != 0)
	{
		while (true)
		{
			std::cv_status status = gate2_.wait_until(lk, abs_time);
			if ((state_ & (write_entered_ | upgradable_entered_)) == 0)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	state_ |= upgradable_entered_;
	return true;
}

template <class Clock, class Duration>
bool
upgrade_mutex::try_unlock_upgrade_and_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	std::unique_lock<mutex_t> lk(mut_);
	if ((state_ & n_readers_) != 1)
	{
		while (true)
		{
			std::cv_status status = gate2_.wait_until(lk, abs_time);
			if ((state_ & n_readers_) == 1)
				break;
			if (status == std::cv_status::timeout)
				return false;
		}
	}
	state_ = write_entered_;
	return true;
}

template <class Mutex> class upgrade_lock;

template <class Mutex>
class shared_lock
{
public:
	typedef Mutex mutex_type;

private:
	mutex_type* m_;
	bool owns_;

	struct __nat {int _;};

public:
	shared_lock()
		: m_(nullptr), owns_(false) {}

	explicit shared_lock(mutex_type& m)
		: m_(&m), owns_(true)
		{m_->lock_shared();}

	shared_lock(mutex_type& m, std::defer_lock_t)
		: m_(&m), owns_(false) {}

	shared_lock(mutex_type& m, std::try_to_lock_t)
		: m_(&m), owns_(m.try_lock_shared()) {}

	shared_lock(mutex_type& m, std::adopt_lock_t)
		: m_(&m), owns_(true) {}

	template <class Clock, class Duration>
		shared_lock(mutex_type& m,
					const std::chrono::time_point<Clock, Duration>& abs_time)
		: m_(&m), owns_(m.try_lock_shared_until(abs_time)) {}
	template <class Rep, class Period>
		shared_lock(mutex_type& m,
					const std::chrono::duration<Rep, Period>& rel_time)
		: m_(&m), owns_(m.try_lock_shared_for(rel_time)) {}

	~shared_lock()
	{
		if (owns_)
			m_->unlock_shared();
	}

	shared_lock(shared_lock const&) = delete;
	shared_lock& operator=(shared_lock const&) = delete;

	shared_lock(shared_lock&& sl)
		: m_(sl.m_), owns_(sl.owns_)
		{sl.m_ = nullptr; sl.owns_ = false;}

	shared_lock& operator=(shared_lock&& sl)
	{
		if (owns_)
			m_->unlock_shared();
		m_ = sl.m_;
		owns_ = sl.owns_;
		sl.m_ = nullptr;
		sl.owns_ = false;
		return *this;
	}

	explicit shared_lock(upgrade_lock<mutex_type>&& ul)
		: m_(ul.mutex()), owns_(ul.owns_lock())
	{
		if (owns_)
			m_->unlock_upgrade_and_lock_shared();
		ul.release();
	}

	explicit shared_lock(std::unique_lock<mutex_type>&& ul)
		: m_(ul.mutex()), owns_(ul.owns_lock())
	{
		if (owns_)
			m_->unlock_and_lock_shared();
		ul.release();
	}

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_until(std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	void swap(shared_lock&& u)
	{
		std::swap(m_, u.m_);
		std::swap(owns_, u.owns_);
	}

	mutex_type* release()
	{
		mutex_type* r = m_;
		m_ = nullptr;
		owns_ = false;
		return r;
	}
	bool owns_lock() const {return owns_;}
	operator int __nat::* () const {return owns_ ? &__nat::_ : 0;}
	mutex_type* mutex() const {return m_;}

};

template <class Mutex>
void
shared_lock<Mutex>::lock()
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
									"shared_lock::lock: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
										   "shared_lock::lock: already locked");
	m_->lock_shared();
	owns_ = true;
}

template <class Mutex>
bool
shared_lock<Mutex>::try_lock()
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
								"shared_lock::try_lock: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
									   "shared_lock::try_lock: already locked");
	owns_ = m_->try_lock_shared();
	return owns_;
}

template <class Mutex>
template <class Clock, class Duration>
bool
shared_lock<Mutex>::try_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
						  "shared_lock::try_lock_until: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
								 "shared_lock::try_lock_until: already locked");
	owns_ = m_->try_lock_shared_until(abs_time);
	return owns_;
}

template <class Mutex>
void
shared_lock<Mutex>::unlock()
{
	if (!owns_)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
								"shared_lock::unlock: not locked");
	m_->unlock_shared();
	owns_ = false;
}

template <class Mutex>
inline
void
swap(shared_lock<Mutex>&  x, shared_lock<Mutex>&  y)
{
	x.swap(y);
}

template <class Mutex>
class upgrade_lock
{
public:
	typedef Mutex mutex_type;

private:
	mutex_type* m_;
	bool owns_;

	struct __nat {int _;};

public:
	upgrade_lock()
		: m_(nullptr), owns_(false) {}

	explicit upgrade_lock(mutex_type& m)
		: m_(&m), owns_(true)
		{m_->lock_upgrade();}

	upgrade_lock(mutex_type& m, std::defer_lock_t)
		: m_(&m), owns_(false) {}

	upgrade_lock(mutex_type& m, std::try_to_lock_t)
		: m_(&m), owns_(m.try_lock_upgrade()) {}

	upgrade_lock(mutex_type& m, std::adopt_lock_t)
		: m_(&m), owns_(true) {}

	template <class Clock, class Duration>
		upgrade_lock(mutex_type& m,
					const std::chrono::time_point<Clock, Duration>& abs_time)
		: m_(&m), owns_(m.try_lock_upgrade_until(abs_time)) {}
	template <class Rep, class Period>
		upgrade_lock(mutex_type& m,
					const std::chrono::duration<Rep, Period>& rel_time)
		: m_(&m), owns_(m.try_lock_upgrade_for(rel_time)) {}

	~upgrade_lock()
	{
		if (owns_)
			m_->unlock_upgrade();
	}

	upgrade_lock(upgrade_lock const&) = delete;
	upgrade_lock& operator=(upgrade_lock const&) = delete;

	upgrade_lock(upgrade_lock&& ul)
		: m_(ul.m_), owns_(ul.owns_)
		{
			ul.m_ = nullptr;
			ul.owns_ = false;
		}

	upgrade_lock& operator=(upgrade_lock&& ul)
	{
		if (owns_)
			m_->unlock_upgrade();
		m_ = ul.m_;
		owns_ = ul.owns_;
		ul.m_ = nullptr;
		ul.owns_ = false;
		return *this;
	}

	upgrade_lock(shared_lock<mutex_type>&& sl, std::try_to_lock_t)
		: m_(nullptr), owns_(false)
	{
		if (sl.owns_lock())
		{
			if (sl.mutex()->try_unlock_shared_and_lock_upgrade())
			{
				m_ = sl.release();
				owns_ = true;
			}
		}
		else
			m_ = sl.release();
	}

	template <class Clock, class Duration>
		upgrade_lock(shared_lock<mutex_type>&& sl,
					 const std::chrono::time_point<Clock, Duration>& abs_time)
		: m_(nullptr), owns_(false)
	{
		if (sl.owns_lock())
		{
			if (sl.mutex()->try_unlock_shared_and_lock_upgrade_until(abs_time))
			{
				m_ = sl.release();
				owns_ = true;
			}
		}
		else
			m_ = sl.release();
	}

	template <class Rep, class Period>
		upgrade_lock(shared_lock<mutex_type>&& sl,
					 const std::chrono::duration<Rep, Period>& rel_time)
		: m_(nullptr), owns_(false)
	{
		if (sl.owns_lock())
		{
			if (sl.mutex()->try_unlock_shared_and_lock_upgrade_for(rel_time))
			{
				m_ = sl.release();
				owns_ = true;
			}
		}
		else
			m_ = sl.release();
	}

	explicit upgrade_lock(std::unique_lock<mutex_type>&& ul)
		: m_(ul.mutex()), owns_(ul.owns_lock())
	{
		if (owns_)
			m_->unlock_and_lock_upgrade();
		ul.release();
	}

	void lock();
	bool try_lock();
	template <class Rep, class Period>
		bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)
		{
			return try_lock_until(std::chrono::steady_clock::now() + rel_time);
		}
	template <class Clock, class Duration>
		bool
		try_lock_until(
					  const std::chrono::time_point<Clock, Duration>& abs_time);
	void unlock();

	void swap(upgrade_lock&& u)
	{
		std::swap(m_, u.m_);
		std::swap(owns_, u.owns_);
	}

	mutex_type* release()
	{
		mutex_type* r = m_;
		m_ = 0;
		owns_ = false;
		return r;
	}

	bool owns_lock() const {return owns_;}
	operator int __nat::* () const {return owns_ ? &__nat::_ : 0;}
	mutex_type* mutex() const {return m_;}
};

template <class Mutex>
void
upgrade_lock<Mutex>::lock()
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
								   "upgrade_lock::lock: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
										  "upgrade_lock::lock: already locked");
	m_->lock_upgrade();
	owns_ = true;
}

template <class Mutex>
bool
upgrade_lock<Mutex>::try_lock()
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
							   "upgrade_lock::try_lock: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
									  "upgrade_lock::try_lock: already locked");
	owns_ = m_->try_lock_upgrade();
	return owns_;
}

template <class Mutex>
template <class Clock, class Duration>
bool
upgrade_lock<Mutex>::try_lock_until(
					   const std::chrono::time_point<Clock, Duration>& abs_time)
{
	if (m_ == nullptr)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
						 "upgrade_lock::try_lock_until: references null mutex");
	if (owns_)
		throw std::system_error(std::error_code(EDEADLK, std::system_category()),
								"upgrade_lock::try_lock_until: already locked");
	owns_ = m_->try_lock_upgrade_until(abs_time);
	return owns_;
}

template <class Mutex>
void
upgrade_lock<Mutex>::unlock()
{
	if (!owns_)
		throw std::system_error(std::error_code(EPERM, std::system_category()),
								"upgrade_lock::unlock: not locked");
	m_->unlock_upgrade();
	owns_ = false;
}

template <class Mutex>
inline
void
swap(upgrade_lock<Mutex>&  x, upgrade_lock<Mutex>&  y)
{
	x.swap(y);
}

template <class ToLock, class FromLock>
class transfer_lock
{
	ToLock to_lock_;
	FromLock& from_lock_;

public:
	explicit transfer_lock(FromLock& fl)
		: to_lock_(std::move(fl)),
		  from_lock_(fl) {}
	~transfer_lock() {from_lock_ = FromLock(std::move(to_lock_));}

	transfer_lock(const transfer_lock&) = delete;
	transfer_lock& operator=(const transfer_lock&) = delete;
};

}  // ting

/*
_LIBCPP_BEGIN_NAMESPACE_STD

template <class Mutex>
inline
unique_lock<Mutex>::unique_lock(ting::upgrade_lock<mutex_type>&& ul)
	: __m_(ul.mutex()), __owns_(ul.owns_lock())
{
	if (__owns_)
		__m_->unlock_upgrade_and_lock();
	ul.release();
}

template <class Mutex>
inline
unique_lock<Mutex>::unique_lock(ting::upgrade_lock<mutex_type>&& ul,
								try_to_lock_t)
	: __m_(nullptr), __owns_(false)
{
	if (ul.owns_lock())
	{
		if (ul.mutex()->try_unlock_upgrade_and_lock())
		{
			__m_ = ul.release();
			__owns_ = true;
		}
	}
	else
		__m_ = ul.release();
}

template <class Mutex>
template <class _Clock, class _Duration>
inline
unique_lock<Mutex>::unique_lock(ting::upgrade_lock<mutex_type>&& ul,
						  const chrono::time_point<_Clock, _Duration>& abs_time)
	: __m_(nullptr), __owns_(false)
{
	if (ul.owns_lock())
	{
		if (ul.mutex()->try_unlock_upgrade_and_lock_until(abs_time))
		{
			__m_ = ul.release();
			__owns_ = true;
		}
	}
	else
		__m_ = ul.release();
}

template <class Mutex>
template <class _Rep, class _Period>
inline
unique_lock<Mutex>::unique_lock(ting::upgrade_lock<mutex_type>&& ul,
								const chrono::duration<_Rep, _Period>& rel_time)
	: __m_(nullptr), __owns_(false)
{
	if (ul.owns_lock())
	{
		if (ul.mutex()->try_unlock_upgrade_and_lock_for(rel_time))
		{
			__m_ = ul.release();
			__owns_ = true;
		}
	}
	else
		__m_ = ul.release();
}

template <class Mutex>
inline
unique_lock<Mutex>::unique_lock(ting::shared_lock<mutex_type>&& sl,
								try_to_lock_t)
	: __m_(nullptr), __owns_(false)
{
	if (sl.owns_lock())
	{
		if (sl.mutex()->try_unlock_shared_and_lock())
		{
			__m_ = sl.release();
			__owns_ = true;
		}
	}
	else
		__m_ = sl.release();
}

template <class Mutex>
template <class _Clock, class _Duration>
inline
unique_lock<Mutex>::unique_lock(ting::shared_lock<mutex_type>&& sl,
						  const chrono::time_point<_Clock, _Duration>& abs_time)
	: __m_(nullptr), __owns_(false)
{
	if (sl.owns_lock())
	{
		if (sl.mutex()->try_unlock_shared_and_lock_until(abs_time))
		{
			__m_ = sl.release();
			__owns_ = true;
		}
	}
	else
		__m_ = sl.release();
}

template <class Mutex>
template <class _Rep, class _Period>
inline
unique_lock<Mutex>::unique_lock(ting::shared_lock<mutex_type>&& sl,
								const chrono::duration<_Rep, _Period>& rel_time)
	: __m_(nullptr), __owns_(false)
{
	if (sl.owns_lock())
	{
		if (sl.mutex()->try_unlock_shared_and_lock_for(rel_time))
		{
			__m_ = sl.release();
			__owns_ = true;
		}
	}
	else
		__m_ = sl.release();
}

_LIBCPP_END_NAMESPACE_STD
*/

#endif
