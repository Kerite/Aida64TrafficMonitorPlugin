#pragma once

#include "traffic_monitor.h"

namespace aida_plugin {
    class Aida64ErrorItem : public IPluginItem {
    public:
        virtual const wchar_t *GetItemName() const override;

        virtual const wchar_t *GetItemId() const override;

        virtual const wchar_t *GetItemLableText() const override;

        virtual const wchar_t *GetItemValueText() const override;

        virtual const wchar_t *GetItemValueSampleText() const override;
    };
}
