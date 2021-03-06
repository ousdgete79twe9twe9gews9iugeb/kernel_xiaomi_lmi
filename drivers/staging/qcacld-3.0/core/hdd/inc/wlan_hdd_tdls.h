/*
 * Copyright (c) 2012-2019 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __HDD_TDLS_H
#define __HDD_TDLS_H
/**
 * DOC: wlan_hdd_tdls.h
 * WLAN Host Device Driver TDLS include file
 */

struct hdd_context;

#ifdef FEATURE_WLAN_TDLS

/* Bit mask flag for tdls_option to FW */
#define ENA_TDLS_OFFCHAN      (1 << 0)  /* TDLS Off Channel support */
#define ENA_TDLS_BUFFER_STA   (1 << 1)  /* TDLS Buffer STA support */
#define ENA_TDLS_SLEEP_STA    (1 << 2)  /* TDLS Sleep STA support */

int wlan_hdd_tdls_get_all_peers(struct hdd_adapter *adapter, char *buf,
				int buflen);

int wlan_hdd_cfg80211_exttdls_enable(struct wiphy *wiphy,
				     struct wireless_dev *wdev,
				     const void *data,
				     int data_len);

int wlan_hdd_cfg80211_exttdls_disable(struct wiphy *wiphy,
				      struct wireless_dev *wdev,
				      const void *data,
				      int data_len);

int wlan_hdd_cfg80211_exttdls_get_status(struct wiphy *wiphy,
					 struct wireless_dev *wdev,
					 const void *data,
					 int data_len);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 16, 0))
int wlan_hdd_cfg80211_tdls_oper(struct wiphy *wiphy,
				struct net_device *dev,
				const uint8_t *peer,
				enum nl80211_tdls_operation oper);
#else
int wlan_hdd_cfg80211_tdls_oper(struct wiphy *wiphy,
				struct net_device *dev,
				uint8_t *peer,
				enum nl80211_tdls_operation oper);
#endif

#ifdef TDLS_MGMT_VERSION2
int wlan_hdd_cfg80211_tdls_mgmt(struct wiphy *wiphy,
				struct net_device *dev, u8 *peer,
				u8 action_code, u8 dialog_token,
				u16 status_code, u32 peer_capability,
				const u8 *buf, size_t len);
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0))
int wlan_hdd_cfg80211_tdls_mgmt(struct wiphy *wiphy,
				struct net_device *dev, const uint8_t *peer,
				uint8_t action_code, uint8_t dialog_token,
				uint16_t status_code, uint32_t peer_capability,
				bool initiator, const uint8_t *buf,
				size_t len);
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 16, 0))
int wlan_hdd_cfg80211_tdls_mgmt(struct wiphy *wiphy,
				struct net_device *dev, const uint8_t *peer,
				uint8_t action_code, uint8_t dialog_token,
				uint16_t status_code, uint32_t peer_capability,
				const uint8_t *buf, size_t len);
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0))
int wlan_hdd_cfg80211_tdls_mgmt(struct wiphy *wiphy,
				struct net_device *dev, uint8_t *peer,
				uint8_t action_code, uint8_t dialog_token,
				uint16_t status_code, uint32_t peer_capability,
				const uint8_t *buf, size_t len);
#else
int wlan_hdd_cfg80211_tdls_mgmt(struct wiphy *wiphy,
				struct net_device *dev, uint8_t *peer,
				uint8_t action_code, uint8_t dialog_token,
				uint16_t status_code, const uint8_t *buf,
				size_t len);
#endif
#endif

/**
 * hdd_set_tdls_offchannel() - set tdls off-channel number
 * @hdd_ctx:     Pointer to the HDD context
 * @adapter: Pointer to the HDD adapter
 * @offchannel: tdls off-channel number
 *
 * This function sets tdls off-channel number
 *
 * Return: 0 on success; negative errno otherwise
 */
int hdd_set_tdls_offchannel(struct hdd_context *hdd_ctx,
			    struct hdd_adapter *adapter,
			    int offchannel);

/**
 * hdd_set_tdls_secoffchanneloffset() - set secondary tdls off-channel offset
 * @hdd_ctx:     Pointer to the HDD context
 * @adapter: Pointer to the HDD adapter
 * @offchanoffset: tdls off-channel offset
 *
 * This function sets secondary tdls off-channel offset
 *
 * Return: 0 on success; negative errno otherwise
 */
int hdd_set_tdls_secoffchanneloffset(struct hdd_context *hdd_ctx,
				     struct hdd_adapter *adapter,
				     int offchanoffset);

/**
 * hdd_set_tdls_offchannelmode() - set tdls off-channel mode
 * @hdd_ctx:     Pointer to the HDD context
 * @adapter: Pointer to the HDD adapter
 * @offchanmode: tdls off-channel mode
 * 1-Enable Channel Switch
 * 2-Disable Channel Switch
 *
 * This function sets tdls off-channel mode
 *
 * Return: 0 on success; negative errno otherwise
 */
int hdd_set_tdls_offchannelmode(struct hdd_context *hdd_ctx,
				struct hdd_adapter *adapter,
				int offchanmode);
int hdd_set_tdls_scan_type(struct hdd_context *hdd_ctx, int val);
int wlan_hdd_tdls_antenna_switch(struct hdd_context *hdd_ctx,
				 struct hdd_adapter *adapter,
				 uint32_t mode);

/**
 * wlan_hdd_cfg80211_configure_tdls_mode() - configure tdls mode
 * @wiphy:   pointer to wireless wiphy structure.
 * @wdev:    pointer to wireless_dev structure.
 * @data:    Pointer to the data to be passed via vendor interface
 * @data_len:Length of the data to be passed
 *
 * Return:   Return the Success or Failure code.
 */
int wlan_hdd_cfg80211_configure_tdls_mode(struct wiphy *wiphy,
					struct wireless_dev *wdev,
					const void *data,
					int data_len);

QDF_STATUS hdd_tdls_register_peer(void *userdata, uint32_t vdev_id,
				  const uint8_t *mac, uint16_t sta_id,
				  uint8_t qos);

QDF_STATUS hdd_tdls_deregister_peer(void *userdata, uint32_t vdev_id,
				    uint8_t sta_id);

/**
 * hdd_init_tdls_config() - initialize tdls config
 * @tdls_cfg: pointer to tdls_start_params structure
 *
 * Return: none
 */
void hdd_init_tdls_config(struct tdls_start_params *tdls_cfg);

#else

static inline int wlan_hdd_tdls_antenna_switch(struct hdd_context *hdd_ctx,
					       struct hdd_adapter *adapter,
					       uint32_t mode)
{
	return 0;
}

static inline int wlan_hdd_cfg80211_configure_tdls_mode(struct wiphy *wiphy,
					struct wireless_dev *wdev,
					const void *data,
					int data_len)
{
	return 0;
}

static inline
QDF_STATUS hdd_tdls_register_peer(void *userdata, uint32_t vdev_id,
				  const uint8_t *mac, uint16_t sta_id,
				  uint8_t qos)
{
	return QDF_STATUS_SUCCESS;
}

static inline
QDF_STATUS hdd_tdls_deregister_peer(void *userdata, uint32_t vdev_id,
				    uint8_t sta_id)
{
	return QDF_STATUS_SUCCESS;
}

static inline void hdd_init_tdls_config(struct tdls_start_params *tdls_cfg)
{
}

#endif /* End of FEATURE_WLAN_TDLS */
#endif /* __HDD_TDLS_H */
