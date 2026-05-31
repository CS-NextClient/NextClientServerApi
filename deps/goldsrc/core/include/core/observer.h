/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <core/delegate.h>
#include <algorithm>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace core
{
    template <typename... Args>
    class Observable
    {
        static inline std::int32_t next_id_{};
        std::vector<std::pair<std::int32_t, Delegate<void(Args...)>>> observers_{};

    public:
        /**
         * @brief Constructor.
        */
        Observable() = default;

        /**
         * @brief Destructor.
        */
        virtual ~Observable() = default;

        /**
         * @brief Move constructor.
        */
        Observable(Observable&&) = default;

        /**
         * @brief Copy constructor.
        */
        Observable(const Observable&) = default;

        /**
         * @brief Move assignment operator.
        */
        Observable& operator=(Observable&&) = default;

        /**
         * @brief Copy assignment operator.
        */
        Observable& operator=(const Observable&) = default;

        /**
         * @brief N/D
         *
         * @return The unique identifier that can be used to unsubscribe.
        */
        std::int32_t Subscribe(Delegate<void(Args...)>&& observer)
        {
            observers_.emplace_back(std::make_pair(next_id_++, std::forward<Delegate<void(Args...)>>(observer)));
            return observers_.back().first;
        }

        /**
         * @brief N/D
         *
         * @tparam Candidate Function or member to connect to the delegate.
         *
         * @return The unique identifier that can be used to unsubscribe.
        */
        template <auto Candidate>
        std::int32_t Subscribe()
        {
            return Subscribe({DELEGATE_ARG<Candidate>});
        }

        /**
         * @brief N/D
         *
         * @tparam Candidate Function or member to connect to the delegate.
         * @tparam Type Type of class or type of payload.
         *
         * @param value_or_instance A valid object that fits the purpose.
         *
         * @return The unique identifier that can be used to unsubscribe.
        */
        template <auto Candidate, typename Type>
        std::int32_t Subscribe(const Type* const value_or_instance)
        {
            return Subscribe({DELEGATE_ARG<Candidate>, value_or_instance});
        }

        /**
         * @brief N/D
         *
         * @param function Function to connect to the delegate.
         * @param payload User defined arbitrary data.
         *
         * @return The unique identifier that can be used to unsubscribe.
        */
        std::int32_t Subscribe(typename Delegate<void(Args...)>::FunctionType function,
                               const void* const payload = nullptr)
        {
            return Subscribe({function, payload});
        }

        /**
         * @brief N/D
         *
         * @param id The unique identifier.
        */
        void Unsubscribe(const std::int32_t id)
        {
            observers_.erase(
                std::remove_if(observers_.begin(), observers_.end(), [id](const auto& element) {
                    return element.first == id;
                }),
                observers_.end());
        }

    protected:
        /**
         * @brief Notify observers.
         *
         * @param args The callback arguments.
        */
        void Notify(Args&&... args) const
        {
            for (const auto& observer : observers_) {
                observer.second(std::forward<Args>(args)...);
            }
        }
    };

    template <typename T>
    class SubscriptionRaii
    {
        std::shared_ptr<T> observable_{};
        std::int32_t subscription_id_{};

    public:
        /**
         * @brief Constructor.
        */
        SubscriptionRaii() = default;

        /**
         * @brief Constructor.
        */
        SubscriptionRaii(std::shared_ptr<T> observable, const std::int32_t subscription_id)
            : observable_(std::move(observable)), subscription_id_(subscription_id)
        {
        }

        /**
         * @brief Destructor.
        */
        ~SubscriptionRaii()
        {
            if (observable_) {
                observable_->Unsubscribe(subscription_id_);
            }
        }

        /**
         * @brief Move constructor.
        */
        SubscriptionRaii(SubscriptionRaii&&) = default;

        /**
         * @brief Copy constructor.
        */
        SubscriptionRaii(const SubscriptionRaii&) = default;

        /**
         * @brief Move assignment operator.
        */
        SubscriptionRaii& operator=(SubscriptionRaii&&) = default;

        /**
         * @brief Copy assignment operator.
        */
        SubscriptionRaii& operator=(const SubscriptionRaii&) = default;
    };
}
