#pragma once

#include <windows.h>
#include <map>

#include "traffic_monitor.h"
#include "aida64_error_item.h"

namespace aida_plugin {
    class AIDA64Plugin : ITMPlugin {
    private:
        static AIDA64Plugin m_instance;
        static Aida64ErrorItem m_error;
        LPCTSTR pBuffer = nullptr;
        HANDLE hAidaFile;
        bool bDataError = false;
        std::map<std::string, IPluginItem *> itemMap;

        AIDA64Plugin();

    public:
        static AIDA64Plugin &Instance();

        virtual IPluginItem *GetItem(int index) override;

        virtual void DataRequired() override;

        virtual const wchar_t *GetInfo(PluginInfoIndex index) override;

        virtual OptionReturn ShowOptionsDialog(void *hParent) override;

        virtual void OnExtenedInfo(ExtendedInfoIndex index, const wchar_t *data) override;
    };

}

__declspec(dllexport) ITMPlugin *TMPluginGetInstance();
