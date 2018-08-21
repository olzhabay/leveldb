#ifndef STORAGE_LEVELDB_UTIL_PERF_LOG_H
#define STORAGE_LEVELDB_UTIL_PERF_LOG_H

#include <cstdio>
#include <cstdint>
#include <sys/time.h>
#include "histogram.h"

namespace leveldb {

namespace  benchmark {

enum Type {
  QUERY_FILE = 0,
  VERSION = 1,
  BLOCK_READ = 2,
  MEMTABLE = 3,
  INDEX_READ = 5,
  QUERY_BLOCK = 6,
  BLOOM_FILTER = 7,
  QUERY_VALUE = 8,
  FILE_ACCESS = 9,
  TABLE_CACHE = 10,
};

class PerfLog {
public:
  PerfLog() {
    query_file_.Clear();
    version_.Clear();
    block_.Clear();
    memtable_.Clear();
    index_read_.Clear();
    query_block_.Clear();
    bloom_filter_.Clear();
    query_value_.Clear();
    file_access_.Clear();
    table_cache_.Clear();
  }

  ~PerfLog() = default;

  void LogMicro(Type type, uint64_t micros) {
    switch (type) {
      case QUERY_FILE:
        query_file_.Add(micros);
        break;
      case VERSION:
        version_.Add(micros);
        break;
      case BLOCK_READ:
        block_.Add(micros);
        break;
      case MEMTABLE:
        memtable_.Add(micros);
        break;
      case INDEX_READ:
        index_read_.Add(micros);
        break;
      case QUERY_BLOCK:
        query_block_.Add(micros);
        break;
      case BLOOM_FILTER:
        bloom_filter_.Add(micros);
        break;
      case QUERY_VALUE:
        query_value_.Add(micros);
        break;
      case FILE_ACCESS:
        file_access_.Add(micros);
        break;
      case TABLE_CACHE:
        table_cache_.Add(micros);
        break;
    }
  }

  std::string GetInfo() {
    std::string r;
    r.append("Memtable info,\n");
    r.append(memtable_.GetInfo());
    r.append("Version info,\n");
    r.append(version_.GetInfo());
    r.append("Query File info,\n");
    r.append(query_file_.GetInfo());
    r.append("Index Block read info\n");
    r.append(index_read_.GetInfo());
    r.append("Query Block info\n");
    r.append(query_block_.GetInfo());
    r.append("Bloom Filter info\n");
    r.append(bloom_filter_.GetInfo());
    r.append("Block Read info,\n");
    r.append(block_.GetInfo());
    r.append("Query Value info\n");
    r.append(query_value_.GetInfo());
    r.append("File Access info\n");
    r.append(file_access_.GetInfo());
    r.append("Table Cache info\n");
    r.append(table_cache_.GetInfo());
    return r;
  }

  std::string GetHistogram() {
    std::string r;
    r.append("Memtable info,\n");
    r.append(memtable_.GetHistogram());
    r.append("Version info,\n");
    r.append(version_.GetHistogram());
    r.append("Query File info,\n");
    r.append(query_file_.GetHistogram());
    r.append("Index Block read info\n");
    r.append(index_read_.GetHistogram());
    r.append("Query Block info\n");
    r.append(query_block_.GetHistogram());
    r.append("Bloom Filter info\n");
    r.append(bloom_filter_.GetHistogram());
    r.append("Block Read info,\n");
    r.append(block_.GetHistogram());
    r.append("Query Value info\n");
    r.append(query_value_.GetHistogram());
    r.append("File Access info\n");
    r.append(file_access_.GetHistogram());
    r.append("Table Cache info\n");
    r.append(table_cache_.GetHistogram());
    return r;
  }

private:
  Histogram query_file_;
  Histogram version_;
  Histogram block_;
  Histogram memtable_;
  Histogram index_read_;
  Histogram query_block_;
  Histogram bloom_filter_;
  Histogram query_value_;
  Histogram file_access_;
  Histogram table_cache_;
};

extern void CreatePerfLog();
extern uint64_t NowMicros();
extern void LogMicros(Type, uint64_t);
extern std::string GetInfo();
extern std::string GetHistogram();
extern void ClosePerfLog();

} // namespace benchmark

} // namespace leveldb

#endif // STORAGE_LEVELDB_UTIL_PERF_LOG_H
