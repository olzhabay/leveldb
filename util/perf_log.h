#ifndef STORAGE_LEVELDB_UTIL_PERF_LOG_H
#define STORAGE_LEVELDB_UTIL_PERF_LOG_H

#include <cstdio>
#include <cstdint>
#include <sys/time.h>
#include <map>
#include "histogram.h"

namespace leveldb {

namespace  benchmark {

enum Type {
  MEMTABLE,
  VERSION,
  QUERY_FILE,
  INDEX_READ,
  QUERY_BLOCK,
  BLOOM_FILTER,
  BLOCK_READ,
  QUERY_VALUE,
  VALUE_COPY,
  FILE_ACCESS,
  BLOCK_READ_ITER,
  LEVEL0_FILES,
};

static const Type AllTypes[] = { MEMTABLE, VERSION, QUERY_FILE, INDEX_READ, QUERY_BLOCK, BLOOM_FILTER, BLOCK_READ,
                                 QUERY_VALUE,VALUE_COPY, FILE_ACCESS, BLOCK_READ_ITER, LEVEL0_FILES};

class PerfLog {
public:
  PerfLog() {
    names_.insert({Type::MEMTABLE, "Memtable"});
    names_.insert({Type::VERSION, "Version"});
    names_.insert({Type::QUERY_FILE, "Query for file"});
    names_.insert({Type::INDEX_READ, "Read for index block"});
    names_.insert({Type::QUERY_BLOCK, "Query for data block"});
    names_.insert({Type::BLOOM_FILTER, "Bloom filter"});
    names_.insert({Type::BLOCK_READ, "Read for data block"});
    names_.insert({Type::QUERY_VALUE, "Query for value"});
    names_.insert({Type::VALUE_COPY, "Copy for value"});
    names_.insert({Type::FILE_ACCESS, "File Accesses"});
    names_.insert({Type::BLOCK_READ_ITER, "Block iterator init"});
    names_.insert({Type::LEVEL0_FILES, "LEVEL0 Files"});
    for (const auto type : AllTypes) {
      histograms_.insert({type, Histogram()});
    }
    Clear();
  }

  ~PerfLog() = default;

  void Clear() {
    for (const auto type : AllTypes) {
      histograms_.at(type).Clear();
    }
  }

  void LogMicro(Type type, uint64_t micros) {
    histograms_.at(type).Add(micros);
  }

  std::string GetInfo() {
    std::string r;
    for (const auto type : AllTypes) {
      r.append(names_.at(type));
      r.append("\n");
      r.append(histograms_.at(type).GetInfo());
    }
    return r;
  }

  std::string GetHistogram() {
    std::string r;
    for (const auto type : AllTypes) {
      r.append(names_.at(type));
      r.append("\n");
      r.append(histograms_.at(type).GetHistogram());
    }
    return r;
  }

private:
  std::map<Type, Histogram> histograms_;
  std::map<Type, std::string> names_;
};

extern void CreatePerfLog();
extern void ClearPerfLog();
extern uint64_t NowMicros();
extern void LogMicros(Type, uint64_t);
extern std::string GetInfo();
extern std::string GetHistogram();
extern void ClosePerfLog();

} // namespace benchmark

} // namespace leveldb

#endif // STORAGE_LEVELDB_UTIL_PERF_LOG_H
