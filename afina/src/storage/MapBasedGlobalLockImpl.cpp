#include "MapBasedGlobalLockImpl.h"

#include <mutex>

namespace Afina {
namespace Backend {

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Put(const std::string &key, const std::string &value)
{
  size_t needed_size = key.size() + value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  auto value_it = _backend.find(key);
  if (value_it != _backend.end())
  {
    needed_size -= value_it->second.size();
    _cache.remove(key);
  }

  while (needed_size > _max_size - _size)
  {
    const std::string old_key = _cache.front();
    _size -= old_key.size();
    _size -= _backend.find(old_key)->second.size();
    _cache.pop_front();
    _backend.erase(old_key);
  }
  _size += needed_size;
  _backend[key] = value;
  if (value_it != _backend.end())
  {
    _cache.push_back(&(value_it->first))
  } else {
    return false;
  }
  return true;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::PutIfAbsent(const std::string &key, const std::string &value)
{
  const size_t needed_size = key.size() + value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  if (_backend.find(key) == _backend.end())
  {
    while (needed_size > _max_size - _size)
    {
      const std::string old_key = _cache.front();
      _size -= old_key.size();
      _size -= _backend.find(old_key)->second.size();
      _cache.pop_front();
      _backend.erase(old_key);
    }
    _size += needed_size;
    _backend[key] = value;
    value_it = _backend.find(key)
    if (value_it != _backend.end())
    {
      _cache.push_back(&(value_it->first))
    } else {
      return false;
    }
    return true;
  }

  return false;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Set(const std::string &key, const std::string &value)
{
  size_t needed_size = key.size() + value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  auto value_it = _backend.find(key)
  if (value_it != _backend.end())
  {
    needed_size -= value_it->second.size();
    while (needed_size > _max_size - _size)
    {
      const std::string old_key = _cache.front();
      _size -= old_key.size();
      _size -= _backend.find(old_key)->second.size();
      _cache.pop_front();
      _backend.erase(old_key);
    }
    _size += needed_size;
    _cache.remove(key);
    _backend[key] = value;
    _cache.push_back(&(value_it->first))
    return true;
  }

  return false;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Delete(const std::string &key) { return false; }

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Get(const std::string &key, std::string &value) const
{
  auto value_it = _backend.find(key)
  if (value_it != _backend.end())
  {
    _cache.remove(key);
    _cache.push_back(&(value_it->first));
    value = value_it->second;
    return true;
  }

  return false;
}

} // namespace Backend
} // namespace Afina
