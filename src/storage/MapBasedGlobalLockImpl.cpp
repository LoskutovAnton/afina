#include "MapBasedGlobalLockImpl.h"

namespace Afina {
namespace Backend {

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Put(const std::string &key, const std::string &value)
{
  std::lock_guard<std::mutex> lock(_lock);

  size_t needed_size = key.size() + value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  auto cache_it = _backend.find(key);
  if (cache_it != _backend.end())
  {
    _cache.splice(_cache.begin(), _cache, cache_it->second);
    _cache.front().second = value;
    return true;
  }

  while (needed_size > _max_size - _size)
  {
    auto old_key = _cache.back();
    _size -= old_key.first.size();
    _size -= old_key.second.size();
    _cache.pop_back();
    _backend.erase(old_key.first);
  }
  _size += needed_size;
  _cache.push_front(std::make_pair(key, value));
  _backend[_cache.front().first] = _cache.begin();
  return true;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::PutIfAbsent(const std::string &key, const std::string &value)
{
  std::lock_guard<std::mutex> lock(_lock);

  const size_t needed_size = key.size() + value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  if (_backend.find(key) == _backend.end())
  {
    while (needed_size > _max_size - _size)
    {
      auto old_key = _cache.back();
      _size -= old_key.first.size();
      _size -= old_key.second.size();
      _cache.pop_back();
      _backend.erase(old_key.first);
    }
    _size += needed_size;
    _cache.push_front(std::make_pair(key, value));
    _backend[_cache.front().first] = _cache.begin();
    return true;
  }


  return false;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Set(const std::string &key, const std::string &value)
{
  std::lock_guard<std::mutex> lock(_lock);

  size_t needed_size = value.size();
  if (needed_size > _max_size)
  {
    return false;
  }

  auto cache_it = _backend.find(key);
  if (cache_it != _backend.end())
  {
    _cache.splice(_cache.begin(), _cache, cache_it->second);
    needed_size -= _cache.front().second.size();
    while (needed_size > _max_size - _size)
    {
      auto old_key = _cache.back();
      _size -= old_key.first.size();
      _size -= old_key.second.size();
      _cache.pop_back();
      _backend.erase(old_key.first);
    }
    _cache.front().second = value;
    return true;
  }

  return false;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Delete(const std::string &key)
{
  std::lock_guard<std::mutex> lock(_lock);

  auto cache_it = _backend.find(key);
  _cache.erase(cache_it->second);
  _backend.erase(cache_it);
  return true;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Get(const std::string &key, std::string &value) const
{
  std::lock_guard<std::mutex> lock(_lock);
  auto cache_it = _backend.find(key);
  if (cache_it != _backend.end())
  {
    _cache.splice(_cache.begin(), _cache, cache_it->second);
    value = _cache.front().second;
    return true;
  }

  return false;
}

} // namespace Backend
} // namespace Afina
