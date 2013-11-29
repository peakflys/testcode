void HandleWrite()
{
	while (true) {
		// 应用层缓冲区全部写到TCP缓冲区了, 此时TCP缓冲区还是可写
		// et模式下不会再通知应用层, 所以设置下socket writable状态
		// 下次应用层数据来的时候检查该状态
		if (write_list_.TotalSize() == 0) {
			socket_.set_is_writable(true);
			return;
		}
		int n = write(fd, write_list_.ReadPoint(), write_list_.readable_size());
		const int error_no = errno;
		if (n == -1) { // 写异常
			if (error_no == EINTR) {
				continue;
			}
			// 缓冲区已写满, 需要等写事件
			if (error_no == EAGAIN) {
				socket_.set_is_writable(false);
				return;
			} else {
				HandleError(error_no);
				return;
			}
		} else { // 写正常
			write_list_.ReadAdvance(n);
		}
	}
}
