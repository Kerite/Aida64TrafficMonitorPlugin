#include <string>

#include "aida64_plugin.h"

namespace aida_plugin {
    AIDA64Plugin AIDA64Plugin::m_instance;

    const std::string shared_memory_name("AIDA64_SensorValues");

    AIDA64Plugin::AIDA64Plugin() {
        hAidaFile = OpenFileMapping(FILE_MAP_READ, FALSE, shared_memory_name.c_str());
        if (hAidaFile == nullptr) {
            this->bDataError = true;
        }
    }

    AIDA64Plugin &AIDA64Plugin::Instance() {
        return m_instance;
    }

    IPluginItem *AIDA64Plugin::GetItem(int index) {
        if (this->bDataError) {
            return &m_error;
        }
        return nullptr;
    }

    void AIDA64Plugin::DataRequired() {
        pBuffer = (LPCTSTR) MapViewOfFile(this->hAidaFile, FILE_MAP_READ, 0, 0, 0);
        if (pBuffer == nullptr) {
            this->bDataError = true;
        }
    }
}