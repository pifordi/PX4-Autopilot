/****************************************************************************
 *
 *   Copyright (c) 2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 *
 * Proof of concept module publishing custom uORB topics
 *
 * This is a material for the 'uORB Explained' espisode of the PX4 Explained Series
 * on the px4.io blog.
 *
 * @author Junwoo Hwang <junwoo091400@gmail.com>
 */

#include <px4_platform_common/log.h>

#include <uORB/uORB.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/pasta_cook.h>
#include <uORB/topics/pasta_order.h>


__EXPORT int uorb_explained_main(int argc, char *argv[]);

class uORBExplained : public ModuleBase<uORBExplained>
{
public:
	uORBExplained();
	~uORBExplained();

	/** @see ModuleBase */
	static int task_spawn(int argc, char *argv[]);

	static int custom_command(int argc, char *argv[]);

	/** @see ModuleBase */
	static int print_usage(const char *reason = nullptr);

	bool init();

private:
	void publishTorqueSetpoint(const hrt_abstime &timestamp_sample);
	void publishThrustSetpoint(const hrt_abstime &timestamp_sample);

	/**
	 * Publication for the 'pasta_cook'
	 *
	 * WAITER -> [pasta_cook] -> CHEF
	 *
	 * Imaginary topic where a 'waiter' orders the 'chef' to cook a certain pasta.
	 */
	uORB::PublicationData<pasta_information_s> _pasta_cook_pub{ORB_ID(pasta_cook)};

	/**
	 * Publication for the 'pasta_order'
	 *
	 * CUSTOMER -> [pasta_cook] -> WAITER
	 *
	 * Imaginary topic where a 'customer' orders the 'waiter' to order a pasta.
	 */
	uORB::PublicationData<pasta_information_s> _pasta_order_pub{ORB_ID(pasta_order)};

	void Run() override;
};
