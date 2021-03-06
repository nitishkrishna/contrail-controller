/*
 * Copyright (c) 2013 Juniper Networks, Inc. All rights reserved.
 */

#ifndef vnsw_agent_vm_uve_entry_h
#define vnsw_agent_vm_uve_entry_h

#include <uve/vm_uve_entry_base.h>
#include <uve/stats_manager.h>

//The class that defines data-structures to store VirtualMachine information
//required for sending VirtualMachine UVE.
class VmUveEntry : public VmUveEntryBase {
public:
    VmUveEntry(Agent *agent, const string &vm_name);
    virtual ~VmUveEntry();
    void UpdatePortBitmap(uint8_t proto, uint16_t sport, uint16_t dport);
    bool FrameVmStatsMsg(UveVirtualMachineAgent *uve,
                         VirtualMachineStats *stats_uve,
                         bool *stats_uve_changed);
    void UpdateFloatingIpStats(const FipInfo &fip_info);
    VmUveEntryBase::FloatingIp * FipEntry(uint32_t fip, const std::string &vn,
                                      Interface *intf);
    virtual void Reset();
protected:
    uint64_t GetVmPortBandwidth
        (StatsManager::InterfaceStats *s, bool dir_in) const;
    L4PortBitmap port_bitmap_;
private:
    bool SetVmPortBitmap(UveVirtualMachineAgent *uve);
    bool FrameInterfaceStatsMsg(const VmInterface *vm_intf,
                                VmInterfaceStats *s_intf) const;
    bool FrameFipStatsMsg(const VmInterface *vm_intf,
                        std::vector<VmFloatingIPStats> &fip_list,
                        std::vector<VmFloatingIPStatSamples> &diff_list) const;
    bool UveVmFipStatsListChanged(const vector<VmFloatingIPStats> &new_l) const;
    DISALLOW_COPY_AND_ASSIGN(VmUveEntry);
};
#endif // vnsw_agent_vm_uve_entry_h
