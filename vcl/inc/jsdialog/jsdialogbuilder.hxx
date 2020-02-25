#ifndef INCLUDED_VCL_INC_JSDIALOG_JSDIALOG_HXX
#define INCLUDED_VCL_INC_JSDIALOG_JSDIALOG_HXX

#include <vcl/weld.hxx>
#include <comphelper/string.hxx>
#include <vcl/sysdata.hxx>
#include <vcl/virdev.hxx>
#include <vcl/builder.hxx>
#include <salvtables.hxx>
#include <vcl/combobox.hxx>

class JSDialogSender
{
    VclPtr<vcl::Window> m_aOwnedToplevel;
public:
    JSDialogSender(VclPtr<vcl::Window> aOwnedToplevel)
    : m_aOwnedToplevel(aOwnedToplevel)
    {}

    void notifyDialogState();
};

class JSInstanceBuilder : public SalInstanceBuilder
{
public:
    JSInstanceBuilder(weld::Widget* pParent, const OUString& rUIRoot, const OUString& rUIFile);
    virtual std::unique_ptr<weld::Dialog> weld_dialog(const OString& id, bool bTakeOwnership = true) override;
    virtual std::unique_ptr<weld::Label> weld_label(const OString &id, bool bTakeOwnership = false) override;
    virtual std::unique_ptr<weld::Entry> weld_entry(const OString& id, bool bTakeOwnership = false) override;
    virtual std::unique_ptr<weld::ComboBox> weld_combo_box(const OString& id, bool bTakeOwnership = false) override;
};

class JSLabel : public SalInstanceLabel, public JSDialogSender
{
public:
    JSLabel(VclPtr<vcl::Window> aOwnedToplevel, FixedText* pLabel,
            SalInstanceBuilder* pBuilder, bool bTakeOwnership);
    virtual void set_label(const OUString& rText) override;
};

class JSEntry : public SalInstanceEntry, public JSDialogSender
{
public:
    JSEntry(VclPtr<vcl::Window> aOwnedToplevel, ::Edit* pEntry,
            SalInstanceBuilder* pBuilder, bool bTakeOwnership);
    virtual void set_text(const OUString& rText) override;
};

class JSListBox : public SalInstanceComboBoxWithoutEdit, public JSDialogSender
{
public:
    JSListBox(VclPtr<vcl::Window> aOwnedToplevel, ::ListBox* pListBox,
                SalInstanceBuilder* pBuilder, bool bTakeOwnership);
    virtual void insert(int pos, const OUString& rStr, const OUString* pId,
                        const OUString* pIconName, VirtualDevice* pImageSurface) override;
    virtual void remove(int pos) override;
};

class JSComboBox : public SalInstanceComboBoxWithEdit, public JSDialogSender
{
public:
    JSComboBox(VclPtr<vcl::Window> aOwnedToplevel, ::ComboBox* pComboBox,
                SalInstanceBuilder* pBuilder, bool bTakeOwnership);
    virtual void insert(int pos, const OUString& rStr, const OUString* pId,
                        const OUString* pIconName, VirtualDevice* pImageSurface) override;
    virtual void remove(int pos) override;
    virtual void set_entry_text(const OUString& rText) override;
};

#endif