// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License.

#pragma once

#include <memory>
#include <mutex>

#include "hnswlib/hnswalg_nm.h"

#include "knowhere/common/Exception.h"
#include "knowhere/index/vector_index/VecIndex.h"

namespace milvus {
namespace knowhere {

class IndexHNSW_SQ8NR : public VecIndex {
 public:
    IndexHNSW_SQ8NR() {
        index_type_ = IndexEnum::INDEX_HNSW_SQ8NR;
    }

    BinarySet
    Serialize(const Config& config = Config()) override;

    void
    Load(const BinarySet& index_binary) override;

    void
    Train(const DatasetPtr& dataset_ptr, const Config& config) override;

    void
    Add(const DatasetPtr& dataset_ptr, const Config& config) override;

    void
    AddWithoutIds(const DatasetPtr&, const Config&) override {
        KNOWHERE_THROW_MSG("Incremental index is not supported");
    }

    DatasetPtr
    Query(const DatasetPtr& dataset_ptr, const Config& config) override;

    int64_t
    Count() override;

    int64_t
    Dim() override;

 private:
    bool normalize = false;
    std::mutex mutex_;
    std::shared_ptr<hnswlib_nm::HierarchicalNSW_NM<float>> index_ = nullptr;
    std::shared_ptr<uint8_t[]> data_ = nullptr;
};

}  // namespace knowhere
}  // namespace milvus
